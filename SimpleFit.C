// make a simple Gaussian Fit in ROOT and RooFit

using namespace RooFit; 

void SimpleFit(const char *inputFile) { 

   TFile * f = new TFile(inputFile);

   TH1F * maa = (TH1F *) f->Get("maa");
 
   TF1 * f2  = new TF1("f2","gausn",50,200);
   f2->SetLineColor(kBlue-3);
   f2->SetParameters(1000,125,1);
   maa->Fit(f2,"R");

}

