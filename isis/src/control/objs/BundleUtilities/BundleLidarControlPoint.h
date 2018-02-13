#ifndef BundleLidarControlPoint_h
#define BundleLidarControlPoint_h
/**
 * @file
 * $Revision: 1.20 $
 * $Date: 2014/5/22 01:35:17 $
 *
 *   Unless noted otherwise, the portions of Isis written by the USGS are
 *   public domain. See individual third-party library and package descriptions
 *   for intellectual property information, user agreements, and related
 *   information.
 *
 *   Although Isis has been used by the USGS, no warranty, expressed or
 *   implied, is made by the USGS as to the accuracy and functioning of such
 *   software and related material nor shall the fact of distribution
 *   constitute any such warranty, and no responsibility is assumed by the
 *   USGS in connection therewith.
 *
 *   For additional information, launch
 *   $ISISROOT/doc//documents/Disclaimers/Disclaimers.html
 *   in a browser or see the Privacy &amp; Disclaimers page on the Isis website,
 *   http://isis.astrogeology.usgs.gov, and the USGS privacy and disclaimers on
 *   http://www.usgs.gov/privacy.html.
 */

#include <QVector>

#include <QSharedPointer>

#include "BundleControlPoint.h"
#include "BundleMeasure.h"
#include "BundleSettings.h"
#include "SparseBlockMatrix.h"
#include "SurfacePoint.h"

namespace Isis {

  class LidarControlPoint;

//  class ControlMeasure;

  /**
   * This class holds information about a lidar control point that BundleAdjust requires.
   * 
   * This class was created to extract functionality from BundleAdjust and wrap a LidarControlPoint
   * with the extra necessary information to correctly perform a bundle adjustment.
   *
   * Note that only non-ignored lidar control points should be used to construct a
   * BundleLidarControlPoint. Similarly, a BundleLidarControlPoint should only contain non-ignored
   * control measures.
   * 
   * @author 2018-02-08 Ken Edmundson
   *
   * @internal
   *   @history 2018-02-08 Ken Edmundson - Original version.
   */
  class BundleLidarControlPoint : public BundleControlPoint {

    public:
      BundleLidarControlPoint(LidarControlPoint *point);
//      BundleLidarControlPoint(const BundleLidarControlPoint &src);
      ~BundleLidarControlPoint();

      // copy
      BundleLidarControlPoint &operator=(const BundleLidarControlPoint &src);// ??? not implemented
      void copy(const BundleLidarControlPoint &src);

      // mutators

      // accessors
//      LidarControlPoint *rawLidarControlPoint() const;

      // string format methods
  };

  // typedefs
  //! Definition a shared pointer to a BundleLidarControlPoint.
  typedef QSharedPointer<BundleLidarControlPoint> BundleLidarControlPointQsp;
}

#endif // BundleLidarControlPoint_h
