#ifndef MatrixSceneWidget_H
#define MatrixSceneWidget_H

#include <QWidget>

#include "XmlStackedHandler.h"

template <typename A> class QList;
class QGraphicsPolygonItem;
class QGraphicsRectItem;
class QGraphicsScene;
class QGraphicsSceneContextMenuEvent;
class QMenu;
class QProgressBar;
class QRubberBand;
class QStatusBar;
class QToolBar;
class QToolButton;

namespace Isis {
  class CorrelationMatrix;
  class Directory;
  class DisplayProperties;
  class FileName;
  class MatrixDisplayTool;
  class MatrixGraphicsView;
//   class MatrixOptions;
  class ProgressBar;
  class Project;
  class PvlGroup;
  class PvlObject;
  class ToolPad;

  /**
   * @brief This widget encompasses the entire matrixDisplay scene
   *
   * This widget is a self-contained view of the correlation matrix resulting from a bundle adjust.
   * It uses Qt's graphics scene/view framework. This widget holds the graphics scene, view, and
   * items. It will also hold the options dialog for the matrix.
   *
   * @ingroup Visualization Tools
   *
   * @author 2014-05-10 Kimberly Oyama
   *
   * @internal
   *   @history 2014-07-14 Kimberly Oyama - Original Version
   */
  class MatrixSceneWidget : public QWidget {
      Q_OBJECT

    public:
      MatrixSceneWidget(QStatusBar *status,
                        bool showTools,
                        bool internalizeToolBarsAndProgress,
                        Directory *directory,
                        QWidget *parent = 0);
      virtual ~MatrixSceneWidget();

      MatrixGraphicsView *getView() const;
      QGraphicsScene *getScene() const;

      bool contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

      void drawGrid(CorrelationMatrix *matrix);
      void drawElements(CorrelationMatrix *matrix);

      QProgressBar *getProgress();
      PvlObject toPvl() const;
      void fromPvl(const PvlObject &);
      void load(XmlStackedHandlerReader *xmlReader);

      QRectF elementsBoundingRect() const;
      Directory *directory() const;
      QList<QAction *> getViewActions();
      QList<QAction *> supportedActions(CorrelationMatrix *matrix);
      void redrawItems();

      void repaintItems(bool colorScheme);
    
      /**
       * Return an empty list of actions for unknown data types
       */
      template <typename DataType>
      QList<QAction *> supportedActions(DataType) {
        return QList<QAction *>();
      }

    signals:
// add roll over
      void mouseEnter();
      void mouseMove(QPointF);
      void mouseLeave();
      void mouseDoubleClick(QPointF);
      void mouseButtonPress(QPointF, Qt::MouseButton s);
      void mouseButtonRelease(QPointF, Qt::MouseButton s);
      void mouseWheel(QPointF, int delta);
      void rubberBandComplete(QRectF r, Qt::MouseButton s);
      void visibleRectChanged(QRectF);

      void elementsChanged();

      void queueSelectionChanged();

    protected:
      virtual bool eventFilter(QObject *obj, QEvent *ev);

    private:
      /**
       * @author 2014-05-10 Steven Lambright
       *
       * @internal
       */
      class XmlHandler : public XmlStackedHandler {
        public:
          XmlHandler(MatrixSceneWidget *scene);
          ~XmlHandler();

          virtual bool startElement(const QString &namespaceURI, const QString &localName,
                                    const QString &qName, const QXmlAttributes &atts);
          virtual bool characters(const QString &ch);
          virtual bool endElement(const QString &namespaceURI, const QString &localName,
                                  const QString &qName);

        private:
          Q_DISABLE_COPY(XmlHandler);

          QString m_characterData;
          MatrixSceneWidget *m_sceneWidget;

          int m_scrollBarXValue;
          int m_scrollBarYValue;
      };
      
    private slots:
      void exportView();
      void saveList();

      void fitInView();

      void sendVisibleRectChanged();
      
    private:
      // methods
      QList<double> getSelectedElements() const;

      // member variables
      Directory *m_directory;
      
      QGraphicsScene *m_graphicsScene; //!< The graphics scene holds the scene items.
      MatrixGraphicsView *m_graphicsView; //!< The graphics view that displays the scene

      QGraphicsRectItem *m_outlineRect; //!< Rectangle outlining the area where the images go.

      QAction *m_quickMapAction;

      ProgressBar *m_progress;

//       MatrixOptions *m_matrixOptions;
  };
}

#endif
