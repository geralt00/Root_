#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include <string>
#include <string.h>
#include "TString.h"
#include "TLorentzVector.h"
#include <iostream>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <math.h>
#include "TH1F.h"
#include "TH2F.h"

//using namespace std;
void mvmvd()
{
  gROOT->Reset();
  gROOT->SetStyle("Pub");

  gStyle->SetOptTitle(0);

  gStyle->SetLabelFont(42, "xyz");
  gStyle->SetLabelSize(0.06, "xyz");
  gStyle->SetLabelOffset(0.015, "xyz");

  gStyle->SetTitleFont(42, "xyz");
  gStyle->SetTitleSize(0.05, "xyz");
  gStyle->SetTitleOffset(1.5, "xyz");

  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.15);

  //  TH2F *dvm = new TH2F("dvm", "dvm", 100, -0.05, 0.05, 100, 2.25, 2.35);
  //TH2F *dvm = new TH2F("dvm", "dvm", 100, 2.25, 2.35, 100, 2.25, 2.35);
  TH3F *dvm = new TH2F("dvm", "dvm", 100, 2.25, 2.35, 100, 2.25, 2.35, 100, -0.05, 0.05)

      TLine *f1 = new TLine(-0.012, 0, -0.012, 2.35);
  TLine *f2 = new TLine(0.015, 0, 0.015, 2.35);
  TLine *f3 = new TLine(-0.05, 2.28221, 0.05, 2.28221);
  TLine *f4 = new TLine(-0.05, 2.29123, 0.05, 2.29123);

  if (1)
  {

    TChain *t_data = new TChain("tree");

    t_data->Add("m3.root");

    Double_t mbc, deltaE, mlambdac;

    t_data->SetBranchAddress("mbc", &mbc);
    t_data->SetBranchAddress("deltaE", &deltaE);
    t_data->SetBranchAddress("mlambdac", &mlambdac);

    for (int i = 0; i < t_data->GetEntries(); i++)
    {
      t_data->GetEntry(i);
      {
        dvm->Fill(mlambdac, mbc, deltaE);
      }
    }
  }

  TCanvas *ca = new TCanvas("ca", "ca", 0, 0, 800, 600);
  //  dvm->GetYaxis()->SetTitle("M_{(p^{+}k^{+}#pi^{-})}");
  dvm->GetYaxis()->SetTitle("M_{bc}");
  //  dvm->GetXaxis()->SetTitle("#DeltaE");
  dvm->GetXaxis()->SetTitle("M_{(p^{+}k^{+}#pi^{-})}");
  dvm->GetZaxis()->SetTitle("#DeltaE");
  //  dvm->SetMarkerColor(4);
  gPad->SetLeftMargin(0.2);
  dvm->SetNdivisions(505, "x");
  dvm->SetNdivisions(505, "y");
  dvm->SetNdivisions(505, "z");
  f1->Draw();
  f2->Draw();
  f3->Draw();
  f4->Draw();
  dvm->Draw("");
  //  dvm_mc->SetMarkerColor(2);
  //  dvm_mc->Draw("same");
  leg = new TLegend(0.7, 0.7, 0.9, 0.9);
  leg->AddEntry(dvm, "date", "p");
  //  leg->AddEntry(dvm_mc,  "MC",    "p");
  leg->SetFillColor(10);

  cout << "n_aft=" << dvm->Integral() << endl;
}
