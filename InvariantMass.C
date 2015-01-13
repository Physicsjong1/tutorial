/*
root -l -b -q tutorial/InvariantMass.C'("step_1.root", "step_1_plots.root")'
*/

//------------------------------------------------------------------------------

#include <vector>

void InvariantMass(const char *inputFile, const char *outputFile)
{
 gSystem->Load("libDelphes");

 // Create chain of root trees
 TChain chain("Delphes");
 chain.Add(inputFile);

 // Create object of class ExRootTreeReader
 ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
 Long64_t numberOfEntries = treeReader->GetEntries();

 // Get pointers to branches used in this analysis
 TClonesArray *branchJet  = treeReader->UseBranch("Jet");

 // Book histograms
 TH1 *histnbjet = new TH1F("nbjet", "Number of b-jets", 5, 0.0, 5.0);
 TH1 *histMbb = new TH1F("mbb", "M_{inv}(b, b)", 75, 50.0, 200.0);

 Int_t numberOfSelectedEvents = 0;

 vector<Jet *> bJets;

 Double_t mbb;
 TLorentzVector p4[2];
 Jet *jet;

 Int_t entry, i;

 // Loop over all events
 for(entry = 0; entry < numberOfEntries; ++entry)
 {
   if(entry%1000 == 0) cout << "event number: " << entry << endl;

   // Load selected branches with data from specified event
   treeReader->ReadEntry(entry);

   bJets.clear();

   for(i = 0; i < branchJet->GetEntriesFast(); ++i)
   {
     jet = (Jet*) branchJet->At(i);
     if(jet->BTag) bJets.push_back(jet);
   }

   histnbjet->Fill(bJets.size());

   // select events with at least 2 b-jets and 2 opposite sign muons
   if(bJets.size() < 2) continue;

   // define four final-state objects

   p4[0] = bJets[0]->P4();
   p4[1] = bJets[1]->P4();

   // leptons must come from a Z decay

   mbb = ((p4[0]) + (p4[1])).M();

   ++numberOfSelectedEvents;

   histMbb->Fill(mbb);

 }

 TFile *fout = TFile::Open(outputFile,"RECREATE");
 fout->cd();

 histnbjet->Write();
 histMbb->Write();

}
