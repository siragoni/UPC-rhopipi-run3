// Copyright 2019-2020 CERN and copyright holders of ALICE O2.
// See https://alice-o2.web.cern.ch/copyright for details of the copyright holders.
// All rights not expressly granted are reserved.
//
// This software is distributed under the terms of the GNU General Public
// License v3 (GPL Version 3), copied verbatim in the file "COPYING".
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

#include "Framework/runDataProcessing.h"
#include "Framework/AnalysisTask.h"
#include "Framework/AnalysisDataModel.h"
#include "Common/DataModel/EventSelection.h"
#include "iostream"
#include <TH1D.h>
#include <TH2D.h>
#include <TString.h>

using namespace std;
using namespace o2;
using namespace o2::framework;
using namespace o2::framework::expressions;



// some table definition for skimmed Data
namespace o2::aod
{

  namespace udcollision
  {
    // general information
    DECLARE_SOA_COLUMN(RunNumber, runNumber, int32_t); //! run number
    DECLARE_SOA_COLUMN(GlobalBC, globalBC, uint64_t);  //! global BC instead of BC ID since candidate may not have a corresponding record in BCs table
    DECLARE_SOA_COLUMN(NetCharge, netCharge, int8_t);  //! Sum of track signs
    DECLARE_SOA_COLUMN(TotalFT0AmplitudeA, totalFT0AmplitudeA, float); //! sum of amplitudes on A side of FT0
    DECLARE_SOA_COLUMN(TotalFT0AmplitudeC, totalFT0AmplitudeC, float); //! sum of amplitudes on C side of FT0
    DECLARE_SOA_COLUMN(TimeFT0A, timeFT0A, float);                     //! FT0A average time
    DECLARE_SOA_COLUMN(TimeFT0C, timeFT0C, float);                     //! FT0C average time

    // FDD information
    DECLARE_SOA_COLUMN(TotalFDDAmplitudeA, totalFDDAmplitudeA, float); //! sum of amplitudes on A side of FDD
    DECLARE_SOA_COLUMN(TotalFDDAmplitudeC, totalFDDAmplitudeC, float); //! sum of amplitudes on C side of FDD
    DECLARE_SOA_COLUMN(TimeFDDA, timeFDDA, float);                     //! FDDA average time
    DECLARE_SOA_COLUMN(TimeFDDC, timeFDDC, float);                     //! FDDC average time
    // FV0A information
    DECLARE_SOA_COLUMN(TotalFV0AmplitudeA, totalFV0AmplitudeA, float); //! sum of amplitudes on A side of FDD
    DECLARE_SOA_COLUMN(TimeFV0A, timeFV0A, float);                     //! FV0A average time
    DECLARE_SOA_COLUMN(TriggerMaskFV0A, triggerMaskFV0A, uint8_t);     //! FV0 trigger mask

  } // end ud collision custom columns



  DECLARE_SOA_TABLE(UDCollisions, "AOD", "UDCOLLISION",
                  o2::soa::Index<>,
                  udcollision::GlobalBC,
                  udcollision::RunNumber,
                  collision::PosX,
                  collision::PosY,
                  collision::PosZ,
                  collision::NumContrib,
                  udcollision::NetCharge,
                  udcollision::TotalFT0AmplitudeA,
                  udcollision::TotalFT0AmplitudeC,
                  udcollision::TimeFT0A,
                  udcollision::TimeFT0C,
                  udcollision::TotalFDDAmplitudeA,
                  udcollision::TotalFDDAmplitudeC,
                  udcollision::TimeFDDA,
                  udcollision::TimeFDDC,
                  udcollision::TotalFV0AmplitudeA,
                  udcollision::TimeFV0A); //end declare udcollision table

using UDCollision = UDCollisions::iterator;

  



  namespace udrhotrack
  {
    DECLARE_SOA_INDEX_COLUMN(UDCollision, udCollision);
    DECLARE_SOA_COLUMN(Px, px, float);
    DECLARE_SOA_COLUMN(Py, py, float);
    DECLARE_SOA_COLUMN(Pz, pz, float);
    DECLARE_SOA_COLUMN(Sign, sign , int);


  } // namespace udrhotrack

DECLARE_SOA_TABLE(UDRhoTracks, "AOD", "UDRhoTrack", o2::soa::Index<>,
                    udrhotrack::Px,
                    udrhotrack::Py,
                    udrhotrack::Pz,
                    udrhotrack::Sign);

using UDRhoTrack = UDRhoTracks::iterator;



namespace udfwdtrack
  {
    DECLARE_SOA_INDEX_COLUMN(UDCollision, udCollision);
    DECLARE_SOA_COLUMN(Px, px, float);
    DECLARE_SOA_COLUMN(Py, py, float);
    DECLARE_SOA_COLUMN(Pz, pz, float);
    DECLARE_SOA_COLUMN(Sign, sign , int);

  } // namespace udfwdtrack

DECLARE_SOA_TABLE(UDFWDTracks, "AOD", "UDFwdTrack", o2::soa::Index<>,
                    udfwdtrack::Px,
                    udfwdtrack::Py,
                    udfwdtrack::Pz,
                    udfwdtrack::Sign);




  using UDFWDTrack = UDFWDTracks::iterator;

} // namespace o2::aod


// end of table definition



struct UPCRhoTableProducer {
  // defining histograms using histogram registry
  HistogramRegistry registry{"registry", {}, OutputObjHandlingPolicy::AnalysisObject};


  Produces<aod::UDFWDTracks> udfwdTracks;

  Produces<aod::UDRhoTracks> udrhoTracks;

  Produces<aod::UDCollisions> udCollision;

  void init(o2::framework::InitContext&) // to initialize histograms 
  {


  }

  void processdata(aod::Collisions const& collision, aod::BCs const& bcs, aod::FwdTracks const& tracksMuon)
  {
      //registry.fill(HIST("hSelectionCounter"), 0);
      
      
      


  } // end of process data


  void processmc(aod::Collisions const& collision, aod::BCs const& bcs, aod::FwdTracks const& tracksMuon)
  {
      //registry.fill(HIST("hSelectionCounter"), 0);
      
      
      


  } // end of process data

PROCESS_SWITCH(UPCRhoTableProducer, processdata, "Process data", true);

PROCESS_SWITCH(UPCRhoTableProducer, processmc, "Process MC data", false);


}; // end of struct

WorkflowSpec defineDataProcessing(ConfigContext const& cfgc)
{
  return WorkflowSpec{
    adaptAnalysisTask<UPCRhoTableProducer>(cfgc)};
}
