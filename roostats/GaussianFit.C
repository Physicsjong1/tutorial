// make a simple Gaussian Fit in ROOT and RooFit


using namespace RooFit; 

void GaussianFit(int n = 500) { 

   TH1D * h1 = new TH1D("h1","Gaussian Fit",100,-5,5);
   h1->FillRandom("gaus", n);

   TF1 * f1  = new TF1("f1","gausn",-5,5);
   f1->SetLineColor(kBlue);
   f1->SetParameters(100,0,1);

   // Neyman chi2 fit
   TFitResultPtr r1 = h1->Fit(f1,"S");

   TF1 * f2  = new TF1("f2","gausn",-5,5);
   f2->SetLineColor(kBlue-3);
   f2->SetParameters(100,0,1);

   // Pearson chi2 fit
   TFitResultPtr r2 = h1->Fit(f2,"P + S");

   TF1 * f3  = new TF1("f3","gausn",-5,5);
   f3->SetLineColor(kRed);
   f3->SetParameters(100,0,1);

   // Binnel likelihood fit
   TFitResultPtr r3 = h1->Fit(f3,"L + S");


   TLegend * l = new TLegend(0.65,0.55,0.88,0.7);
   l->AddEntry(f1,"Neyman chi2","l");
   l->AddEntry(f2,"Person chi2","l");
   l->AddEntry(f3,"Binned ML  ","l");
   l->Draw();

   // do now the fit with RooFit

   RooWorkspace w("w");
   // define a Gaussian pdf
   w.factory("Gaussian:g(x[-5,5],mu[0,-10,10],sigma[1,0,1000])");
   // create extend pdf with number of events
   w.factory("ExtendPdf:model(g,nevt[100,0,100000])");   

   RooAbsPdf * pdf = w.pdf("model");   // access object from workspace
   RooRealVar * x = w.var("x");   // access object from workspace
   

   // generate n gaussian measurement for a Gaussian(x, 0, 1);
   //RooDataSet * data = pdf->generate( *x);
   //data->SetName("unbinData");  

   // create dataset
   RooDataHist * data = new RooDataHist("data","data",*x,h1); 


   new TCanvas(); 
   // RooFit plotting capabilities 
   RooPlot * pl = x->frame(Title("Gaussian Fit")); 
   data->plotOn(pl); 
   pl->Draw(); 

   w.var("sigma")->setVal(1);
   w.var("mu")->setVal(0);

   // now fit the data set 
   RooFitResult * r4 = pdf->fitTo(*data, Minimizer("Minuit2","Migrad"), Save(1) ); 
 

   // plot the pdf on the same RooPlot object we have plotted the data 
   pdf->plotOn(pl);
   pdf->paramOn(pl, Layout(0.6,0.9,0.85));

   pl->Draw();

   // import data in workspace (IMPORTANT for saving it )
   w.import(*data); 

   w.Print();

   // write workspace in the file (recreate file if already existing)
   w.writeToFile("GaussianModel.root", true);

   cout << "model written to file " << endl;

   std::cout << "\nResult of Neyman chi2 \n";
   r1->Print();
   std::cout << "\nResult of Pearson chi2 \n";
   r2->Print();
   std::cout << "\nResult of Binned Likelihood \n";
   r3->Print();
   std::cout << "\nResult of Binned Likelihood fit with ROOTFIT\n";
   r4->Print();


}

