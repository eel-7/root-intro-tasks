#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "TH1.h"
#include "TF1.h"
#include "TLegend.h"
#include "TPad.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "TGaxis.h"
#include "TStyle.h"

#define DEBUG


int main(int argc, char** argv) {

    std::string filename;
    std::string filename_graph;

    if (argc == 3) {
        filename = argv[1];
        filename_graph = argv[2];
    }
    else {
        std::cout << "Usage `./Histos <filename.pdf> <filename_graph.pdf>`" << std::endl;
        return 1;
    }

    char outFileOpen[1024];
    char outFileClose[1024];
    char outFileAdd[1024];
    char outFileGraph[1024];

    sprintf(outFileOpen, "%s[", filename.c_str());
    sprintf(outFileClose, "%s]", filename.c_str());
    sprintf(outFileAdd, "%s", filename.c_str());
    sprintf(outFileGraph, "%s", filename_graph.c_str());

    gStyle->SetTitleSize(0.04,"xyz");
    gStyle->SetLabelSize(0.04,"xyz");
    gStyle->SetTitleOffset(1.1,"x");

    TGaxis::SetMaxDigits(3);

    TCanvas *S = new TCanvas();

    S->SetLeftMargin(0.10);

    S->Print(outFileOpen);

    TH1F *h1 = new TH1F("h1", "h1", 100, -20, 20);

    // loop to fill the histogram with random numbers

    int N = 1000;

    // std::vector<int> N_array = {1, 10, 100, 1000, 10000, 100000, 1000000};
    double N_array[7] = {1, 10, 100, 1000, 10000, 100000, 1000000};

    // std::vector<int> x_error(7,0);
    double x_error[7] = {0};

    // std::vector<double> mean_array(7,0);
    double mean_array[7] = {0};

    // std::vector<double> mean_error_array(7,0);
    double mean_error_array[7] = {0};

    for (int j=0; j<7; ++j) {

        N=N_array[j];

        h1->Reset("ICES");

        for (int i=0; i<N; ++i) {
            h1->Fill(gRandom->Gaus(-1, 5));
        }

        h1->SetTitle(";x;Counts");

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

        mean_array[j] = mean;
        mean_error_array[j] = mean_error;

        char mean_label[1024];
        char stddev_label[1024];
        char n_label[1024];

        sprintf(mean_label, "%s%.2f#pm%.2f", "#mu = ", mean, mean_error);
        sprintf(stddev_label, "%s%.2f#pm%.2f", "#sigma = ", stddev, stddev_error);
        sprintf(n_label, "N=%i", N);

        TLatex latex;
        latex.SetNDC();
        latex.SetTextAlign(11);

        latex.SetTextFont(42);
        latex.SetTextSize(0.04);

        latex.DrawLatex(0.14, 0.7, mean_label);
        latex.DrawLatex(0.14, 0.65, stddev_label);

#ifdef DEBUG
        std::cout << "[DEBUG] par0 = " << r->Parameter(0) << std::endl;
        std::cout << "[DEBUG] par1 = " << r->Parameter(1) << std::endl;
        std::cout << "[DEBUG] par2 = " << r->Parameter(2) << std::endl;
#endif


        S->Print(outFileAdd);

        S->Clear();
    }

    TGraphErrors *g1 = new TGraphErrors(7,N_array, mean_array, x_error, mean_error_array);

    gPad->SetLogx();

    g1->SetTitle(";Number of entries;Mean");

    g1->Draw();

    S->Print(outFileAdd);

    S->Print(outFileGraph);

    S->Print(outFileClose);

    return 0;
}
