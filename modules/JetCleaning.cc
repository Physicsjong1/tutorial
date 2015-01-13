//-----------------------------------------------------------------------------
// modules/JetCleaning.cc
//-----------------------------------------------------------------------------

#include "modules/JetCleaning.h"

#include "classes/DelphesClasses.h"
#include "classes/DelphesFactory.h"
#include "classes/DelphesFormula.h"

#include "ExRootAnalysis/ExRootResult.h"
#include "ExRootAnalysis/ExRootFilter.h"

#include "TMath.h"
#include "TString.h"
#include "TFormula.h"
#include "TRandom3.h"
#include "TObjArray.h"
#include "TDatabasePDG.h"
#include "TLorentzVector.h"
#include "TVector3.h"

#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;


//------------------------------------------------------------------------------

JetCleaning::JetCleaning() :
  fItCandidateInputArray(0), fItJetInputArray(0)
{
}

//------------------------------------------------------------------------------

JetCleaning::~JetCleaning()
{
}

//------------------------------------------------------------------------------

void JetCleaning::Init()
{
  fDeltaRMin = GetDouble("DeltaRMin", 20);

  // import input array(s)

  fCandidateInputArray = ImportArray(GetString("CandidateInputArray", "MuonMomentumSmearing/muons"));
  fItCandidateInputArray = fCandidateInputArray->MakeIterator();

  fJetInputArray = ImportArray(GetString("JetInputArray", "FastJetFinder/jets"));
  fItJetInputArray = fJetInputArray->MakeIterator();

  // create output array

  fOutputArray = ExportArray(GetString("OutputArray", "electrons"));
}

//------------------------------------------------------------------------------

void JetCleaning::Finish()
{
  if(fItJetInputArray) delete fItJetInputArray;
  if(fItCandidateInputArray) delete fItCandidateInputArray;
}

//------------------------------------------------------------------------------

void JetCleaning::Process()
{
  Candidate *jet, *candidate;
  Double_t deltaR = 5.0;

  // loop over all input leptons

  fItCandidateInputArray->Reset();
  while((candidate = static_cast<Candidate*>(fItCandidateInputArray->Next())))
  {
    const TLorentzVector &candidateMomentum = candidate->Momentum;

    // loop over all input jets
    fItJetInputArray->Reset();

    while((jet = static_cast<Candidate*>(fItJetInputArray->Next())))
    {
      const TLorentzVector &jetMomentum = jet->Momentum;

      Double_t dr = candidateMomentum.DeltaR(jetMomentum);
     
      if( dr < deltaR ) deltaR = dr;
    }

    candidate->DeltaR = deltaR;

    if(deltaR < fDeltaRMin) continue;

    fOutputArray->Add(candidate);
  }
}


//-----------------------------------------------------------------------------
