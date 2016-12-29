// make a simple Gaussian Fit in ROOT and RooFit

using namespace RooFit; 

void SimpleRooFit(const char *inputFile) { 

   TFile * f = new TFile(inputFile);

   TH1F * h1 = (TH1F *) f->Get("maa");

   RooRealVar x("x","x",115,135);
   RooRealVar mu("mu","mu",125.0,100,150);
   RooRealVar sigma("sigma","sigma",2.0,0.0,5.0); 
   RooGaussian gauss("gauss","gaussian PDF",x,mu,sigma) ; 
   RooRealVar nsig("nsig","signal events",3000,0,5000); 
   RooAddPdf model("model","model",RooArgList(gauss),RooArgList(nsig));
  
   RooDataHist data("data","dataset with x",x,h1);
   model.fitTo(data);

   new TCanvas();
   RooPlot * pl = x.frame(Title("Gaussian Fit"));
   data.plotOn(pl);
   model.plotOn(pl);
   pl->Draw();
   
}

