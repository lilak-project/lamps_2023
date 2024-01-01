#ifndef LAMPSTPCPADPLANE_HH
#define LAMPSTPCPADPLANE_HH

#include "LKPadPlane.h"
#include "TF1.h"
#include "TH2Poly.h"

class LTPadPlane : public LKPadPlane
{
    public:
        LTPadPlane();
        virtual ~LTPadPlane() {}

        static LTPadPlane* fInstance;
        static LTPadPlane* GetPlane();

        virtual bool Init();

        virtual Int_t FindPadID(Double_t i, Double_t j);
        //virtual Int_t FindPadID(Int_t section, Int_t row, Int_t layer);
        virtual Int_t FindPadID(Int_t section, Int_t layer, Int_t row);
        virtual Double_t PadDisplacement() const;
        virtual bool IsInBoundary(Double_t i, Double_t j);
        virtual void DrawFrame(Option_t *option = "");
        virtual TH2* GetHist(Option_t *option = "-1");
        virtual TCanvas *GetCanvas(Option_t *optiont = "");
        virtual bool SetDataFromBranch();
        virtual void FillDataToHist();

        TH2* GetHist(Int_t selectSection);
        void Draw(Option_t *option="");

        //LKPad* GetPad(Int_t section, Int_t layer, Int_t row) { return GetPad(FindPadID(section,layer,row)); }
        Int_t FindPadID(Int_t cobo, Int_t aget, Int_t asad, Int_t chan);
        LKPad *GetPadFromEleID(Int_t cobo, Int_t aget, Int_t asad, Int_t chan);
        int GetElectronicsID(int cobo, int aget, int asad, int channelID) { return 100000*cobo + 10000*aget + 100*asad + channelID; }

        void GetSectionParameters(Int_t section, Double_t &t1, Double_t &t2, Double_t &xmin, Double_t &xmax, Double_t &ymin, Double_t &ymax);
        void CreateHistograms();

        static void MouseClickEvent1();
        static void MouseClickEvent2();

        void ZoomInWindow(Int_t bin, Double_t x, Double_t y);
        void SelectAndDrawChannel(Int_t bin, Double_t x, Double_t y);

    //public: // LKDetectorPlane
        //virtual void Clear(Option_t *option = "");
        //virtual void Print(Option_t *option = "") const;
        //virtual bool Init() = 0;
        //void SetDetector(LKDetector *detector) { fDetector = detector; }
        //virtual bool IsInBoundary(Double_t i, Double_t j) = 0;
        //virtual Int_t FindChannelID(Double_t i, Double_t j) { return -1; }
        //virtual Int_t FindChannelID(Int_t section, Int_t row, Int_t layer) { return -1; }
        //virtual TCanvas *GetCanvas(Option_t *option = "");
        //virtual int GetNumCPads() { return 1; }
        //virtual TPad *GetCPad(int iPad) { return (TPad*) GetCanvas(); }
        //virtual TH2* GetHist(Option_t *option = "-1") = 0;
        //virtual bool SetDataFromBranch() { return false; }
        //virtual void FillDataToHist() {};
        //virtual void DrawFrame(Option_t *option = "") {}
        //virtual void Draw(Option_t *option = "");
        //TVector3 GlobalToLocalAxis(TVector3 xGlobal) const { return xGlobal; }
        //TVector3 LocalToGlobalAxis(TVector3 xLocal) const { return xLocal; }
        //void SetAxis(axis_t axis1, axis_t axis2);
        //axis_t GetAxis1();
        //axis_t GetAxis2();

    //public: // LKPadPlane
        //virtual void Print(Option_t *option = "") const;
        //virtual void Clear(Option_t *option = "");
        //virtual Int_t FindChannelID(Double_t i, Double_t j) { return -1; }
        //virtual Int_t FindChannelID(Int_t section, Int_t row, Int_t layer) { return -1; }
        //virtual Int_t FindPadID(Double_t i, Double_t j) { return FindChannelID(i,j); }
        //virtual Int_t FindPadID(Int_t section, Int_t row, Int_t layer) { return FindChannelID(section,row,layer); }
        //Double_t PadDisplacement() const { return 0; }
        //virtual bool SetDataFromBranch();
        //virtual void DrawHist();
        //void FillDataToHist();
        //LKPad *GetPadFast(Int_t padID);
        //LKPad *GetPad(Int_t padID);
        //LKPad *GetPad(Double_t i, Double_t j);
        //LKPad *GetPad(Int_t section, Int_t row, Int_t layer);
        //void SetPadArray(TClonesArray *padArray);
        //void SetHitArray(TClonesArray *hitArray);
        //Int_t GetNumPads();
        //void FillBufferIn(Double_t i, Double_t j, Double_t tb, Double_t val, Int_t trackID = -1);
        //virtual void ResetHitMap();
        //virtual void ResetEvent();
        //void AddHit(LKTpcHit *hit);
        //virtual LKTpcHit *PullOutNextFreeHit();
        //void PullOutNeighborHits(vector<LKTpcHit*> *hits, vector<LKTpcHit*> *neighborHits);
        //void PullOutNeighborHits(TVector2 p, Int_t range, vector<LKTpcHit*> *neighborHits);
        //void PullOutNeighborHits(Double_t x, Double_t y, Int_t range, vector<LKTpcHit*> *neighborHits);
        //void PullOutNeighborHits(LKHitArray *hits, LKHitArray *neighborHits);
        //void PullOutNeighborHits(Double_t x, Double_t y, Int_t range, LKHitArray *neighborHits);
        //void GrabNeighborPads(vector<LKPad*> *pads, vector<LKPad*> *neighborPads);
        //TObjArray *GetPadArray();
        //bool PadPositionChecker(bool checkCorners = true);
        //bool PadNeighborChecker();
        //TVector3 DriftElectron(TVector3 xGlobal) const;

    private:
        LKPad *NewPad(Int_t s, Int_t r, Int_t l);
        void SetNeighborPads(LKPad *pad0, LKPad *pad1);
        Int_t FindSection(Double_t i, Double_t j);

    private:
        TF1* fFuncXRightBound = nullptr;
        TF1* fFuncXRightBoundInverse = nullptr;

        Double_t fXMin = -550;
        Double_t fXMax = +550;
        Double_t fYMin = -550;
        Double_t fYMax = +550;
        Double_t fZMin = -350;
        Double_t fZMax = 1350;
        Int_t fZBins = 512;

        TVector2 fPosSectionCorner[8][4];

        Double_t fRMin = 105.;
        Double_t fRMax = 545-41.5;
        //Double_t fRMin = 100.;
        //Double_t fRMax = 510;
        Double_t fPadGap = 0.5;
        Double_t fPadWidth = 3.;
        Double_t fPadHeight = 10.;
        Double_t fRadiusLayer0 = fRMin + 0.5*fPadHeight;
        Double_t fRTopCut = fRMax;
        Int_t fNumLayers = 42;

        Int_t fNumTbs = 512;
        Int_t fMaxWaveformY = 4100;

        Int_t fBinNumberTopView;
        Int_t fBinNumberSideView;

        Double_t fTanPi1o8;
        Double_t fTanPi3o8;
        Double_t fTanPi5o8;
        Double_t fTanPi7o8;
        Double_t fCosPiNo4[8];
        Double_t fSinPiNo4[8];

        int fNumHalfRowsInLayer[50] = {0};
        int fNumPadsDownToLayer[50] = {0}; ///< in single section
        int fNumSkippedHalfRows[50] = {0};

        Double_t fXSpacing;
        Double_t fRSpacing;

        const Bool_t fDoCutTopBoundary = true;
        const Bool_t fDoCutSideBoundary = true;

        int ****fMapCAACToPadID;

        int fSelectedSection = 0;

        TH2Poly* fHistPadPlaneSection[8];
        TH2Poly* fFramePadPlane = nullptr;
        TH2Poly* fHistPadPlane = nullptr;
        //TGraph* fFrameSideView = nullptr;
        TH2D* fHistWaveform = nullptr;
        TH2D* fHistTopView = nullptr;
        TH2D* fHistSideView = nullptr;
        TH1D* fHistChannel1 = nullptr;
        TH1D* fHistChannel2 = nullptr;
        TGraph* fGraphSectionBoundary1 = nullptr;
        TGraph* fGraphSectionBoundary2 = nullptr;
        TGraph* fGraphPadBoundary = nullptr;

        bool fUseChannel1 = true;

        TClonesArray* fBufferArray = nullptr;
        TClonesArray* fHitArray = nullptr;

        TString fFillType = "Buffer";

        int ConvHP(int bin) { return bin-1; }
        int ConvPH(int bin) { return bin+1; }

    public:
        double GetPadCutBoundaryYAtX(double x) { return fTanPi3o8*x; }
        double GetPadCutBoundaryXAtR(double r) { return r/sqrt(1+fTanPi3o8*fTanPi3o8); }
        double GetPadCenterYBoundAtX(double x) { return fTanPi3o8*(x-.5) + 10; }

        Double_t GetRMin()            const { return fRMin; }
        Double_t GetRMax()            const { return fRMax; }
        Double_t GetPadGap()          const { return fPadGap; }
        Double_t GetPadWidth()        const { return fPadWidth; }
        Double_t GetPadHeight()       const { return fPadHeight; }
        Int_t GetNumLayer()        const { return fNumLayers; }
        Double_t GetPadXSpacing()     const { return fXSpacing; }
        Double_t GetPadRSpacing()     const { return fRSpacing; }

        ClassDef(LTPadPlane, 1)
};

#endif
