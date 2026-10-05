#include <cstdio>
#include <iostream>
#include <string>

#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "TH1.h"
#include "TF1.h"
#include "TLegend.h"
#include "TPad.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TLatex.h"

#define DEBUG


int main(int argc, char** argv) {

    std::string filename;

    if (argc == 2) {
        filename = argv[1];
    }
    else {
        std::cout << "Usage `./Histos <filename.pdf>`" << std::endl;
        return 1;
    }

    char outFileOpen[1024];
    char outFileClose[1024];
    char outFileAdd[1024];

    sprintf(outFileOpen, "%s[", filename.c_str());
    sprintf(outFileClose, "%s]", filename.c_str());
    sprintf(outFileAdd, "%s", filename.c_str());

    TCanvas *S = new TCanvas();

    S->Print(outFileOpen);

    TH1F *h1 = new TH1F("h1", "h1", 100, -20, 20);

    // loop to fill the histogram with random numbers

    int N = 1000;

    for (int i=0; i<N; ++i) {
        h1->Fill(gRandom->Gaus(-1, 5));
    }

    h1->Draw();
    TFitResultPtr r = h1->Fit("gaus", "S");

    TF1 *f1 = h1->GetFunction("gaus");

    TLegend *leg = new TLegend(0.12, 0.75, 0.30, 0.9);

    leg->AddEntry(h1, "Histogram");
    leg->AddEntry(f1, "Fit");

    leg->Draw();

    Double_t constant = r->Parameter(0);
    Double_t mean = r->Parameter(1);
    Double_t stddev = r->Parameter(2);

    Double_t constant_error = r->ParError(0);
    Double_t mean_error = r->ParError(1);
    Double_t stddev_error = r->ParError(2);

    TLatex latex;
    latex.SetNDC();
    latex.SetTextAlign(11);

#ifdef DEBUG
    std::cout << "[DEBUG] par0 = " << r->Parameter(0) << std::endl;
    std::cout << "[DEBUG] par1 = " << r->Parameter(1) << std::endl;
    std::cout << "[DEBUG] par2 = " << r->Parameter(2) << std::endl;
#endif


    S->Print(outFileAdd);

    S->Print(outFileClose);

    return 0;
}
