
using namespace RooFit;
using namespace RooStats;
using namespace RooStats::HistFactory;


// make a counting model using the histfactory

TString fileName = "CountingModel_HF.root";

void CountingModel_HF( int nobs=3, double b = 1, double errb = 0.2) {


   TH1D * hobs = new TH1D("hobs","hobs",1,0,1);
   hobs->SetBinContent(1,nobs); 


   TH1D * h1_s = new TH1D("hs","signal  histo",1,0,1);
   h1_s->SetBinContent(1,1);

   
   TH1D * h1_b = new TH1D("hb","bkg  histo",1,0,1);
   h1_b->SetBinContent(1,b);

   
   HistFactory::Measurement meas("CountingModel","CountingModel");
   meas.SetPOI("mu");

   meas.SetLumi(1.0);
   meas.SetLumiRelErr(0.001);  // not relevant 
   // this does not make lumi varying
   meas.AddConstantParam("Lumi");

   HistFactory::Channel channel("SignalRegion"); 
   channel.SetData(hobs);

   HistFactory::Sample signal("signal");
   signal.AddNormFactor("mu",1,0,30);
   //signal.AddOverallSys("sig_unc",0.99, 1.01);
   signal.SetHisto(h1_s); 
   channel.AddSample(signal);

   HistFactory::Sample backg("background");
   //backg.AddNormFactor("taub",b,0,10);
   backg.SetHisto(h1_b);
   backg.AddOverallSys("b_unc",1.-errb, 1+errb);  // b uncertainty
   channel.AddSample(backg);


   meas.AddChannel(channel);
   
   
   
   // make the model 
   RooWorkspace * w = HistFactory::MakeModelAndMeasurementFast(meas);

   // to change interpolation mode to piecewise linear (default is type=4, polynomial interp + exp. exytrapolation)
   HistFactory::FlexibleInterpVar * fl = (HistFactory::FlexibleInterpVar *) w->function("background_SignalRegion_epsilon");
   if (fl) fl->setAllInterpCodes(0);
   else printf("ERROR changing interp code \n");
   
   w->writeToFile(fileName);    

   printf("written model to file for nobs = %d, b = %f \n",nobs, b); 
}
