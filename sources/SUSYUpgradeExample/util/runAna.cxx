// analysis code
#include "xAODRootAccess/Init.h"
#include "SampleHandler/SampleHandler.h"
#include "SampleHandler/ScanDir.h"
#include "SampleHandler/ToolsDiscovery.h"
#include "EventLoop/Job.h"
#include "EventLoop/DirectDriver.h"
#include "SampleHandler/DiskListLocal.h"
#include <TSystem.h>

#include "SUSYUpgradeExample/UpgradeAnalysis.h"
#include "MyPackage/MyAlgorithm.h"

// standard library stuff
#include <iostream>

using namespace std;

//===========================
int main( int argc, char* argv[] ) {
  //===========================

  // Take the submit directory from the input if provided:
  string sample = "bob";
  if( argc > 1 ) sample = argv[ 1 ];
  string submitDir = "/afs/cern.ch/user/j/jerdmani/private/outdir/outdir_"+sample;
  
  // Set up the job for xAOD access:
  xAOD::Init().ignore();

  // Construct the samples to run on:
  //SH::SampleHandler sh;

  // use SampleHandler to scan all of the subdirectories of a directory for particular MC single file:
  //const char* inputFilePath = gSystem->ExpandPathName ("/afs/cern.ch/user/j/jerdmani/private/susyexamples/");
  //cout << inputFilePath;
  //SH::ScanDir().filePattern("DAOD_TRUTH1."+sample+".root").scan(sh,"/afs/cern.ch/user/j/jerdmani/private/susyexamples/");

  //  SH::ScanDir().scanEOS(sh, "/eos/atlas/atlaslocalgroupdisk/dq2/rucio/user/aagaard/51/");

  //eosatlas.cern.ch//eos/atlas/atlaslocalgroupdisk/dq2/rucio/user/aagaard/51//ec/user.aagaard.8879101._000255.DAOD_TRUTH1.TauTauJets.root

  //SH::ScanDir().scanEOS(sh,"/eos/atlas/atlaslocalgroupdisk/susy/aagaard/Higgsino2016/Samples/Backgrounds/DAOD_TRUTH1.ttbarJets.root");
  //SH::ScanDir().scanEOS(sh, "/eos/atlas/atlaslocalgroupdisk/dq2/rucio/user/aagaard/*.root");
  //SH::ScanDir().sampleDepth(0);
  SH::SampleHandler sh;
  SH::readFileList(sh,"sample","/afs/cern.ch/user/j/jerdmani/private/samples/"+sample + ".list");
  
  // SH::ScanDir().scanEOS(sh,"/eos/atlas/atlaslocalgroupdisk/susy/aagaard/Higgsino2016/Samples/Backgrounds/");
  // SH::ScanDir().samplePattern("DAOD_TRUTH1.ttbarJets.root");
  
  //SH::ScanDir().scanEOS(sh,"/eos/atlas/atlaslocalgroupdisk/susy/aagaard/Higgsino2016/Samples/Backgrounds/DAOD_TRUTH1.ttbarJets.root");
  sh.print ();

  //cout << "Big Root File created";
  //  SH::ScanE
  //DAOD_TRUTH1.MC15.999101.MGPy8EG_A14N23LO_C1N2N3_SlepSnu_x0p50_100_1_noFilter.DAOD.root

  // cout << "It did not crash" << endl;
  // Set the name of the input TTree. It's always "CollectionTree"
  // for xAOD files.
  sh.setMetaString( "nc_tree", "CollectionTree" );

  // Print what we found:
  sh.print();

  // Create an EventLoop job:
  EL::Job job;
  job.sampleHandler( sh );
  job.options()->setDouble (EL::Job::optMaxEvents, -1);

  // Add our analysis to the job:
  UpgradeAnalysis* alg = new UpgradeAnalysis();
  job.algsAdd( alg );

  // MyAlgorithm* alg = new MyAlgorithm();
  // job.algsAdd( alg );
  
  // Run the job using the local/direct driver:
  EL::DirectDriver driver;
  driver.submit( job, submitDir );

  return 0;
}
