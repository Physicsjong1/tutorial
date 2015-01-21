/*
root -l -b -q tutorial/InvariantMass.C'("step_1.root", "step_1_plots.root")'
*/

//------------------------------------------------------------------------------

#include <vector>

void IsoAnalyzer(const char *inputFile, const char *outputFile)
{
 gSystem->Load("libDelphes");

 // Create chain of root trees
 TChain chain("Delphes");
 chain.Add(inputFile);

 // Create object of class ExRootTreeReader
 ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
 Long64_t numberOfEntries = treeReader->GetEntries();

 // Get pointers to branches used in this analysis
 TClonesArray *branchMuon  = treeReader->UseBranch("Muon");
 TClonesArray *branchElectron  = treeReader->UseBranch("Electron");

 // Book histograms
 TH1 *nleptons = new TH1F("nleptons", "Number of Leptons", 4, 0.0, 4.0);
 TH1 *relIso = new TH1F("relIso", "Relative Isolation", 100, 0.0, 1.0);

 Int_t numberOfSelectedEvents = 0;

 Muon *muon;
 Electron *electron;

 Int_t entry, i;

 // Loop over all events
 for(entry = 0; entry < numberOfEntries; ++entry)
 {
   if(entry%1000 == 0) cout << "event number: " << entry << endl;

   // Load selected branches with data from specified event
   treeReader->ReadEntry(entry);
   
   Int_t nmuons = 0;
   Int_t nelectrons = 0;

   for(i = 0; i < branchMuon->GetEntriesFast(); ++i)
   {
     muon = (Muon*) branchMuon->At(i);
     if(muon->PT > 20 && abs(muon->Eta) < 2.4) {
       nmuons = nmuons + 1;
       relIso->Fill(muon->RelIso);
     }
   }

   for(i = 0; i < branchElectron->GetEntriesFast(); ++i)
   {
     electron = (Electron*) branchElectron->At(i);
     if(electron->PT > 20 && abs(electron->Eta) < 2.4) {
       nelectrons = nelectrons + 1;
       relIso->Fill(electron->RelIso);
     }
   }

   nleptons->Fill(nmuons+nelectrons);

   ++numberOfSelectedEvents;

 }

 TFile *fout = TFile::Open(outputFile,"RECREATE");
 fout->cd();

 nleptons->Write();
 relIso->Write();

}
