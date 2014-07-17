#ifndef BundleSettings_h
#define BundleSettings_h

/**
 * @file
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

#include <QList>
#include <QVector>
#include <QPair>
#include <QString>

#include "BundleObservationSolveSettings.h"
#include "MaximumLikelihoodWFunctions.h" // why not forward declare???
#include "PvlObject.h"

namespace Isis {
  class MaximumLikelihoodWFunctions;
  class PvlGroup;
  /**
   * @brief Container class for BundleAdjustment settings. 
   * This class contains all of the settings needed to run a bundle adjustment. 
   * A BundleSettings object is passed into the BundleAdjustment constructor.  
   *  
   * @ingroup ControlNetworks
   *
   * @author 2014-05-14 Jeannie Backer
   *
   * @internal
   *   @history 2014-05-14 Jeannie Backer - Original version.
   *  
   */
 class BundleSettings {
   public:
      BundleSettings();
      BundleSettings(const BundleSettings &other);
      ~BundleSettings();

      // copy constructor
      BundleSettings &operator=(const BundleSettings &other);

      void setValidateNetwork(bool validate);
      bool validateNetwork() const;

      // Solve Options
      /**
       * This enum defines the types of solve methods.
       */
      enum SolveMethod {
        Sparse,   //!< Cholesky model sparse normal equations matrix. (Uses the cholmod library).
        SpecialK, //!< Dense normal equations matrix.
      };
      // converter
      static SolveMethod stringToSolveMethod(QString solveMethod);
      static QString solveMethodToString(SolveMethod solveMethod);

      // mutators
      void setSolveOptions(SolveMethod method, 
                           bool solveObservationMode = false,
                           bool updateCubeLabel = false, 
                           bool errorPropagation = false,
                           bool solveRadius = false, 
                           double globalLatitudeAprioriSigma = -1.0, 
                           double globalLongitudeAprioriSigma = -1.0, 
                           double globalRadiusAprioriSigma = -1.0);
      void setSolveMethod(SolveMethod method);
      void setSolveObservationMode(bool observationMode);
      void setSolveRadius(bool radius);
      void setUpdateCubeLabel(bool updateCubeLabel);
      void setErrorPropagation(bool errorPropagation);
      void setOutlierRejection(bool outlierRejection, double multiplier);
      void setObservationSolveOptions(QVector<BundleObservationSolveSettings*>& observationSolveSettings);

      // accessors
      SolveMethod solveMethod() const;
      bool solveObservationMode() const;
      bool solveRadius() const;
      bool updateCubeLabel() const;
      bool errorPropagation() const;
      bool outlierRejection() const;
      double outlierRejectionMultiplier() const;
      double globalLatitudeAprioriSigma() const;
      double globalLongitudeAprioriSigma() const;
      double globalRadiusAprioriSigma() const;

      int numberSolveSettings() { return m_observationSolveSettings.size(); }
      BundleObservationSolveSettings* observationSolveSettings(QString instrumentId);
      BundleObservationSolveSettings* observationSolveSettings(int n)
      { return m_observationSolveSettings[n]; }


      // Convergence Criteria
      /**
       * This enum defines the options for convergence. 
       */
      enum ConvergenceCriteria {
        Sigma0,              /**< Sigma0 will be used to determine that the bundle adjustment has 
                                  converged.*/
        ParameterCorrections /**< All parameter corrections will be used to determine that the 
                                  bundle adjustment has converged.*/
      };
      static ConvergenceCriteria stringToConvergenceCriteria(QString criteria);
      static QString convergenceCriteriaToString(ConvergenceCriteria criteria);
      void setConvergenceCriteria(ConvergenceCriteria criteria, double threshold, 
                                  int maximumIterations);
      ConvergenceCriteria convergenceCriteria() const;
      double convergenceCriteriaThreshold() const;
      int convergenceCriteriaMaximumIterations() const;

      // Parameter Uncertainties (Weighting)
      // mutators
//      void setGlobalLatitudeAprioriSigma(double sigma);
//      void setGlobalLongitudeAprioriSigma(double sigma);
//      void setGlobalRadiiAprioriSigma(double sigma);

      // Maximum Likelihood Estimation Options
      /**
       * This enum defines the options for maximum likelihood estimation. 
       */
      enum MaximumLikelihoodModel {
        NoMaximumLikelihoodEstimator, /**< Do not use a maximum likelihood model.*/
        Huber,                        /**< Use a Huber maximum likelihood model. This model
                                           approximates the L2 norm near zero and the L1 norm
                                           thereafter. This model has one continuous derivative.*/
        ModifiedHuber,                /**< Use a modified Huber maximum likelihood model. This model
                                           approximates the L2 norm near zero and the L1 norm
                                           thereafter. This model has two continuous derivative.*/
        Welsch,                       /**< Use a Welsch maximum likelihood model. This model
                                           approximates the L2 norm near zero, but then decays
                                           exponentially to zero.*/
        Chen                          /**< Use a Chen maximum likelihood model. This is a highly
                                           aggressive model that intentionally removes the largest
                                           few percent of residuals.???? */
      };
      static MaximumLikelihoodWFunctions::Model stringToMaximumLikelihoodModel(QString model);
      static QString maximumLikelihoodModelToString(MaximumLikelihoodWFunctions::Model model);
      void addMaximumLikelihoodEstimatorModel(MaximumLikelihoodWFunctions::Model model, 
                                              double cQuantile);
      QList< QPair< MaximumLikelihoodWFunctions::Model, double > > 
          maximumLikelihoodEstimatorModels() const;

      // Self Calibration ??? (from cnetsuite only)

      // Target Body ??? (from cnetsuite only)

      // Output Options ??? (from Jigsaw only)
      void setOutputFiles(QString outputFilePrefix, bool createBundleOutputFile, 
                          bool createCSVPointsFile, bool createResidualsFile);
      QString outputFilePrefix() const;
      bool createBundleOutputFile() const;
      bool createCSVPointsFile() const;
      bool createResidualsFile() const;

      PvlObject pvlObject(QString name = "BundleSettings") const;

    private:
      bool m_validateNetwork;
      SolveMethod m_solveMethod; //!< Solution method for matrix decomposition.
      bool m_solveObservationMode; //!< for observation mode (explain this somewhere)
      bool m_solveRadius; //!< to solve for point radii
      bool m_updateCubeLabel; //!< update cubes (only here for output into bundleout.txt)
      bool m_errorPropagation; //!< to perform error propagation
      bool m_outlierRejection; //!< to perform automatic outlier detection/rejection
      double m_outlierRejectionMultiplier; // multiplier = 1 if rejection = false

      // QVector of observation solve settings
      QVector<BundleObservationSolveSettings*> m_observationSolveSettings;

      // Parameter Uncertainties (Weighting)
      double m_globalLatitudeAprioriSigma;
      double m_globalLongitudeAprioriSigma;
      double m_globalRadiusAprioriSigma;

      // Convergence Criteria
      ConvergenceCriteria m_convergenceCriteria;
      double m_convergenceCriteriaThreshold;
      int m_convergenceCriteriaMaximumIterations;

      // Maximum Likelihood Estimation Options
      // model and maxModelCQuantile for each of the three maximum likelihood estimations.
      // Note that Welsch and Chen can not be used for the first model.
      QList< QPair< MaximumLikelihoodWFunctions::Model, double > > m_maximumLikelihood;

      // Self Calibration ??? (from cnetsuite only)

      // Target Body ??? (from cnetsuite only)

      // Output Options ??? (from Jigsaw only)
      QString m_outputFilePrefix; //!< output file prefix
      bool m_createBundleOutputFile; //!< to print standard bundle output file (bundleout.txt)
      bool m_createCSVPointsFile; //!< to output points and image station data in csv format
      bool m_createResidualsFile; //!< to output residuals in csv format
 };
};
#endif
