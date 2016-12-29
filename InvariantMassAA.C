/*
root -l -b -q InvariantMassAA.C'("tch.root", "tch_plots.root")'
*/

//------------------------------------------------------------------------------

#include <vector>

void InvariantMassAA(const char *inputFile, const char *outputFile)
{
 gSystem->Load("libDelphes");

 // Create chain of root trees
 TChain chain("Delphes");
 chain.Add(inputFile);

 // Create object of class ExRootTreeReader
 ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
 Long64_t numberOfEntries = treeReader->GetEntries();

 // Get pointers to branches used in this analysis
 TClonesArray *branchPhoton  = treeReader->UseBranch("Photon");

 // Book histograms
 TH1 *histnphoton = new TH1F("nphoton", "Number of photons", 5, 0.0, 5.0);
 TH1 *histMaa = new TH1F("maa", "M_{inv}(a, a)", 100, 70, 170);

 Int_t numberOfSelectedEvents = 0;

 vector<Photon *> photons;

 Double_t maa;
 TLorentzVector p4[2];
 Photon *photon;

 Int_t entry, i;

 // Loop over all events
 for(entry = 0; entry < numberOfEntries; ++entry)
 {
   if(entry%1000 == 0) cout << "event number: " << entry << endl;

   // Load selected branches with data from specified event
   treeReader->ReadEntry(entry);

   photons.clear();

   for(i = 0; i < branchPhoton->GetEntriesFast(); ++i)
   {
     photon = (Photon*) branchPhoton->At(i);
     photons.push_back(photon);
   }

   histnphoton->Fill(photons.size());

   // select events with at least 2 b-jets and 2 opposite sign muons
   if(photons.size() < 2) continue;

   // define four final-state objects

   p4[0] = photons[0]->P4();
   p4[1] = photons[1]->P4();

   // leptons must come from a Z decay

   maa = ((p4[0]) + (p4[1])).M();

   ++numberOfSelectedEvents;

   histMaa->Fill(maa);

 }

 TFile *fout = TFile::Open(outputFile,"RECREATE");
 fout->cd();

 histnphoton->Write();
 histMaa->Write();

}
