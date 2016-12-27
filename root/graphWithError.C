void graphWithError(){

  TCanvas * c1 = new TCanvas("c1","A Simple Graph with error bars",200,10,700,500);
  c1->SetGrid();

  const Int_t n = 10;
  Float_t x[n] = {-.22,.05,.25,.35,.5,.61,.7,.85,.89,.95};
  Float_t y[n] = {1,2.9,5.6,7.4,9,9.6,8.7,6.3,4.5,1};
  // create the error arrays
  Float_t ex[n] = {.05,.1,.07,.07,.04,.05,.06,.07,.08,.05};
  Float_t ey[n] = {.8,.7,.6,.5,.4,.4,.5,.6,.7,.8};

  // create the TGraphErrors and draw it
  TGraph * gr = new TGraphErrors(n,x,y,ex,ey);
  gr->SetTitle("TGraphErrors Example");
  gr->SetMarkerColor(4);
  gr->SetMarkerStyle(21);
  gr->Draw("ALP");

  //title
  //gr->GetXaxis()->SetTitle("Time (s)");
  //gr->GetYaxis()->SetTitle("Distance (m)");
  //gr->GetXaxis()->CenterTitle(); 
  //gr->GetYaxis()->CenterTitle();

}


