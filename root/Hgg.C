{

  //style
  gROOT->SetStyle("Plain");
  gStyle->SetCanvasDefH(500);
  gStyle->SetCanvasDefW(500);
  // Margins:
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.08);

  // For the axis titles:
  gStyle->SetTitleColor(1, "XYZ");
  gStyle->SetTitleFont(42, "XYZ");
  gStyle->SetTitleSize(0.06, "XYZ");
  gStyle->SetTitleXOffset(0.9);
  gStyle->SetTitleYOffset(1.3);

  // For the axis labels:
  gStyle->SetLabelColor(1, "XYZ");
  gStyle->SetLabelFont(42, "XYZ");
  gStyle->SetLabelOffset(0.007, "XYZ");
  gStyle->SetLabelSize(0.04, "XYZ");

  ifstream in;
  in.open("Hgg.txt");

  TH1F *h1 = new TH1F("h1","h10",100,100,200);
  TH1F *h5 = new TH1F("h5","h10",20,100,200);
  TH1F *h10 = new TH1F("h10","h10",10,100,200);

  double x;

  while(in >> x){
    h1->Fill(x);
    h5->Fill(x);
    h10->Fill(x);
  }

  double total_number_of_events = h1->Integral();
 
  h1->Scale( 1.0/(total_number_of_events * h1->GetBinWidth(1)) );
  h5->Scale( 1.0/(total_number_of_events * h5->GetBinWidth(1)) );
  h10->Scale( 1.0/(total_number_of_events * h10->GetBinWidth(1)) );
 
  TCanvas * c = new TCanvas("c","c",1);
  h1->Draw("Hist");
  h5->Draw("Histsame");
  h10->Draw("Histsame");

  h1->SetStats(0);
  h1->SetTitle("Histogram PDF");
  h1->GetXaxis()->SetTitle("Invariant mass (GeV)");
  h1->GetYaxis()->SetTitle("Number of events");

  h1->SetLineColor(1);
  h5->SetLineColor(2);
  h10->SetLineColor(4);

  TLegend l(0.6,0.6,0.85,0.85);
  l.AddEntry(h1,"width=1 GeV","L");
  l.AddEntry(h5,"width=5 GeV","L");
  l.AddEntry(h10,"width=10 GeV","L");
  l.SetTextSize(0.04);
  l.SetFillColor(0);
  l.SetLineColor(0);
  l.Draw();
  c->Print("histograms.pdf");

} 
