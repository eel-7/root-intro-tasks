#include <cstdio>
#include <iostream>
#include <string>

#include "TH1.h"
#include "TRandom.h"
#include "TCanvas.h"



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

    S->Print(outFileAdd);

    S->Print(outFileClose);

    return 0;
}
