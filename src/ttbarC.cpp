/*
 * ttbarC.cpp
 *
 *  Created on: 24 Aug 2016
 *      Author: jkiesele
 */

#include "interface/ttbarC.h"
#include <string>
#include "TObjString.h"
#include <cmath>

void ttbarC::analyze(size_t childid /* this info can be used for printouts */){

    /*
    * This skeleton analyser runs directly on the Delphes output.
    * It can be used to create histograms directly or a skim.
    * If a skim is created, a new input configuration will be written automatically
    * and stored in the output directory together with the ntuples.
    * The skim can contain delphes objects again or can be flat. This is up
    * to the user.
    * Examples for both are given here.
    *
    * The same skeleton can be used to read the skim. Please refer to the comments
    * marked with "==SKIM=="
    *
    * These parts are commented, since the code is supposed to work as an example without
    * modifications on Delphes output directly.
    */



    /*
    * Define the branches that are to be considered for the analysis
    * This branch handler (notice the "d")
    * is used to run directly in Delphes output.
    * For skimmed ntuples, see below
    */
    d_ana::dBranchHandler<Electron> elecs(tree(),"Electron");
    /*
    * Other branches might be the following
    * (for a full list, please inspect the Delphes sample root file with root)
    * For the Delphes class description, see $DELPHES_PATH/classes/DelphesClasses.h
    */
    //
    d_ana::dBranchHandler<HepMCEvent>  event(tree(),"Event");
    d_ana::dBranchHandler<GenParticle> genpart(tree(),"Particle");
    d_ana::dBranchHandler<Jet>         genjet(tree(),"GenJet");
    d_ana::dBranchHandler<Jet>         jet(tree(),"Jet");
    d_ana::dBranchHandler<Muon>        muontight(tree(),"MuonTight");
    d_ana::dBranchHandler<Muon>        muonloose(tree(),"MuonLoose");
    d_ana::dBranchHandler<Photon>      photon(tree(),"Photon");
    d_ana::dBranchHandler<MissingET>   met(tree(),"MissingET");
    d_ana::dBranchHandler<Vertex>      vert(tree(),"Vertex");



    /* ==SKIM==
    *
    * If a skim of the Delphes outout was created in a way indicated
    * further below, use the tBranchHandler (please notive the "t")
    * to access vectors of objects...
    *
    */
    // d_ana::tBranchHandler<std::vector<Electron> > electrons(tree(),"Electrons");

    /*==SKIM==
    *
    * Or an object directly
    *
    */
    //d_ana::tBranchHandler<MissingET> met(tree(),"MET");



    /*
    * Always use this function to add a new histogram (can also be 2D)!
    * Histograms created this way are automatically added to the output file
    */
    //TH1* histo=addPlot(new TH1D("histoname1","histotitle1",100,0,100),"p_{T} [GeV]","N_{e}");
    TH1* histoJetPT = addPlot(new TH1D("JetPT","Jet PT",200,0,200),"p_{T} [GeV]","N_{e}");
    TH1* histoJetEta = addPlot(new TH1D("JetEta","Jet Eta",100,-3,3),"Eta", "N_{e}");
    TH1* histoJetPhi = addPlot(new TH1D("JetPhi","Jet Phi",100,-3,3),"Phi", "N_{e}");

    TH1* histoJetPTee= addPlot(new TH1D("JetPTee","Jet PT Dielectron Channel",200,0,200),"p_{T} [GeV]","N_{e}");
    TH1* histoJetEtaee = addPlot(new TH1D("JetEtaee","Jet Eta Dielectron Channel",100,-3,3),"Eta", "N_{e}");
    TH1* histoJetPhiee = addPlot(new TH1D("JetPhiee","Jet Phi Dielectron Channel",100,-3,3),"Phi", "N_{e}");
    
    TH1* histoJetPTeu = addPlot(new TH1D("JetPTeu","Jet PT eu Channel",200,0,200),"p_{T} [GeV]","N_{e}");
    TH1* histoJetEtaeu = addPlot(new TH1D("JetEtaeu","Jet Eta eu Channel",100,-3,3),"Eta", "N_{e}");
    TH1* histoJetPhieu = addPlot(new TH1D("JetPhieu","Jet Phi eu Channel",100,-3,3),"Phi", "N_{e}");

    TH1* histoJetPTuu = addPlot(new TH1D("JetPTuu","Jet PT Dimuon Channel",200,0,200),"p_{T} [GeV]","N_{e}");
    TH1* histoJetEtauu = addPlot(new TH1D("JetEtauu","Jet Eta Dimuon Channel",100,-3,3),"Eta", "N_{e}");
    TH1* histoJetPhiuu = addPlot(new TH1D("JetPhiuu","Jet Phi Dimuon Channel",100,-3,3),"Phi", "N_{e}");

    TH1* histoElecPT = addPlot(new TH1D("ElecPT","Electron PT",200,0,200),"p_{T} [GeV]","N_{e}");
    TH1* histoElecEta = addPlot(new TH1D("ElecEta","Electron Eta",100,-3,3),"Eta", "N_{e}");
    TH1* histoElecPhi = addPlot(new TH1D("ElecPhi","Electron Phi",100,-3,3),"Phi", "N_{e}");

    TH1* histoElecPTee = addPlot(new TH1D("ElecPTee","Electron PT Dielectron Channel",200,0,200),"p_{T} [GeV]","N_{e}");
    TH1* histoElecEtaee = addPlot(new TH1D("ElecEtaee","Electron Eta Dielectron Channel",100,-3,3),"Eta", "N_{e}");
    TH1* histoElecPhiee = addPlot(new TH1D("ElecPhiee","Electron Phi Dielectron Channel",100,-3,3),"Phi", "N_{e}");

    TH1* histoElecPTeu = addPlot(new TH1D("ElecPTeu","Electron PT eu Channel",200,0,200),"p_{T} [GeV]","N_{e}");
    TH1* histoElecEtaeu = addPlot(new TH1D("ElecEtaeu","Electron Eta eu Channel",100,-3,3),"Eta", "N_{e}");
    TH1* histoElecPhieu = addPlot(new TH1D("ElecPhieu","Electron Phi eu Channel",100,-3,3),"Phi", "N_{e}");

    TH1* histoMuonPT = addPlot(new TH1D("MuonPT","Muon PT",200,0,200),"p_{T} [GeV]","N_{e}");
    TH1* histoMuonEta = addPlot(new TH1D("MuonEta","Muon Eta",100,-3,3),"Eta", "N_{e}");
    TH1* histoMuonPhi = addPlot(new TH1D("MuonPhi","Muon Phi",100,-3,3),"Phi", "N_{e}");

    
    TH1* histoMuonPTeu = addPlot(new TH1D("MuonPTeu","Muon PT eu Channel",200,0,200),"p_{T} [GeV]","N_{e}");
    TH1* histoMuonEtaeu = addPlot(new TH1D("MuonEtaeu","Muon Eta eu Channel",100,-3,3),"Eta", "N_{e}");
    TH1* histoMuonPhieu = addPlot(new TH1D("MuonPhieu","Muon Phi eu Channel",100,-3,3),"Phi", "N_{e}");

    TH1* histoMuonPTuu = addPlot(new TH1D("MuonPTuu","Muon PT Dimuon Channel",200,0,200),"p_{T} [GeV]","N_{e}");
    TH1* histoMuonEtauu = addPlot(new TH1D("MuonEtauu","Muon Eta Dimuon Channel",100,-3,3),"Eta", "N_{e}");
    TH1* histoMuonPhiuu = addPlot(new TH1D("MuonPhiuu","Muon Phi Dimuon Channel",100,-3,3),"Phi", "N_{e}");

    TH1* histoMET = addPlot(new TH1D("MET","MET",200,0,200),"p_{T} [GeV]","N_{e}");
    TH1* histoMETPhi = addPlot(new TH1D("METPhi","MET Phi",100,-3,3),"Phi", "N_{e}");

    TH1* histoMETee = addPlot(new TH1D("METee","MET Dielectron Channel",200,0,200),"p_{T} [GeV]","N_{e}");
    TH1* histoMETPhiee = addPlot(new TH1D("METPhiee","MET Phi Dielectron Channel",100,-3,3),"Phi", "N_{e}");

    TH1* histoMETeu = addPlot(new TH1D("METeu","MET eu Channel",200,0,200),"p_{T} [GeV]","N_{e}");
    TH1* histoMETPhieu = addPlot(new TH1D("METPhieu","MET Phi eu Channel",100,-3,3),"Phi", "N_{e}");

    TH1* histoMETuu = addPlot(new TH1D("METuu","MET Dimuon Channel",200,0,200),"p_{T} [GeV]","N_{e}");
    TH1* histoMETPhiuu = addPlot(new TH1D("METPhiuu","MET Phi Dimuon Channel",100,-3,3),"Phi", "N_{e}");

    TH1* histoNumJet = addPlot(new TH1D("NumJet","Number of Jets",30,0,30),"Jets","N_{e}");

    TH1* histoNumJetee = addPlot(new TH1D("NumJetee","Number of Jets Dielectron Channel",30,0,30),"Jets","N_{e}");

    TH1* histoNumJeteu = addPlot(new TH1D("NumJeteu","Number of Jets eu Channel",30,0,30),"Jets","N_{e}");

    TH1* histoNumJetuu = addPlot(new TH1D("NumJetuu","Number of Jets Dimuon Channel",30,0,30),"Jets","N_{e}");

    TH1* histoNumEvents = addPlot(new TH1D("NumEvents","Number of Events by Type",4,0,4),"Type of Events","N_{e}");

    /*
    * If (optionally) a skim or a flat ntuple is to be created, please use the following function to initialize
    * the tree.
    * The output files will be written automatically, and a config file will be created.
    */
    //TTree* myskim=addTree();

    /*
    * Add a simple branch to the skim
    */
    
    //Double_t elecPt=0;
    //myskim->Branch("elecPt", &elecPt);
    
    /*
    * Or store a vector of objects (also possible to store only one object)
    */
    //std::vector<Electron> skimmedelecs;
    //myskim->Branch("Electrons",&skimmedelecs);

    
    int totalDileptonEvents = 0;
    int eeEvents = 0;
    int euEvents = 0;
    int uuEvents = 0;

    //debugging counters
    int jetMulti = 0;
    int bTag = 0;
    int invMass = 0;
    int metCut = 0;
    
    int numEventsCount = 0;

    //size_t nevents=tree()->entries();
    size_t nevents = 500000;
    //size_t nevents = 1000;
    
    if(isTestMode())
        nevents/=100;
    for(size_t eventno=0;eventno<nevents;eventno++){
        /*
        * The following two lines report the status and set the event link
        * Do not remove!
        */
        reportStatus(eventno,nevents);
        tree()->setEntry(eventno);


        /*
        * Begin the event-by-event analysis
        */

        // Count total number of events processed


        numEventsCount++;
        histoNumEvents->Fill(0);
        
        
        int numJets = 0;
        int numJetsee = 0;
        int numJetseu = 0;
        int numJetsuu = 0;


        bool isDimuon = false;
        bool isDielec = false;
        bool isEMuon = false;

        // execute electron, muon, and jet PT Cuts
        std::vector<size_t> eleInd;
        std::vector<size_t> muonInd;
        std::vector<size_t> jetInd;
        if(elecs.size()>0){
            for(size_t i=0;i<elecs.size();i++){
                if(elecs.at(i)->PT > 20 && elecs.at(i)->Eta < 2.4 && elecs.at(i)->Eta > -2.4 && !(((elecs.at(i)->Eta > 1.4442) && (elecs.at(i)->Eta < 1.5660)) || ((elecs.at(i)->Eta < -1.4441) && (elecs.at(i)->Eta > -1.5660)))){
                    eleInd.push_back(i);
                }
            }
        }
        
        for(size_t i=0;i<muonloose.size();i++){
            if(muonloose.at(i)->PT > 20 && muonloose.at(i)->Eta > -2.4 && muonloose.at(i)->Eta < 2.4){   
                muonInd.push_back(i);
            }
        }

        //Find Leading and Next to leading electron and muon
        int leadElec;
        if(eleInd.size() > 0)
            leadElec = eleInd.at(0);
        int secElec = 0;

        int leadMuon;
        if(muonInd.size() > 0)
                    leadMuon = muonInd.at(0);
        int secMuon = 0;

        if(eleInd.size() >= 2){
            secElec = eleInd.at(1);
            for(size_t i=1;i<eleInd.size();i++){
                if(elecs.at(eleInd.at(i))->PT > elecs.at(leadElec)->PT){
                    secElec = leadElec;
                    leadElec = eleInd.at(i);
                }
                else if(elecs.at(eleInd.at(i))->PT > elecs.at(secElec)->PT)
                    secElec = eleInd.at(i);
            }
        }

        if(muonInd.size() >= 2){
            secMuon = muonInd.at(1);
            for(size_t i=1;i<muonInd.size();i++){
                if(muonloose.at(muonInd.at(i))->PT > muonloose.at(leadMuon)->PT){
                    secMuon = leadMuon;
                    leadMuon = muonInd.at(i);
                }
                else if(muonloose.at(muonInd.at(i))->PT > muonloose.at(secMuon)->PT)
                    secMuon = muonInd.at(i);
            }
        }   
        

        // determine dilepton type
    
        // EU if exactly 1 e and 1 u
        if(eleInd.size() == 1 && muonInd.size() == 1){
            euEvents++;
            isEMuon = true;
            histoNumEvents->Fill(1);
        }
        // EE if at least 2 electrons and 0 muons
        else if(eleInd.size() >= 2 && muonInd.size() == 0){
            eeEvents++;
            isDielec = true;
            histoNumEvents->Fill(2);
        }
        // UU if at least 2 muons and 0 electrons
        else if(muonInd.size() >= 2 && eleInd.size() == 0){
            uuEvents++;
            isDimuon = true;
            histoNumEvents->Fill(3);
        }
        // Check for at least 2 Electrons
        else if(eleInd.size() >= 2){
            // Check for 2+ E and 2+ U
            if(muonInd.size() >=2){
                // EE if both electrons are higher PT than leading muon
                if(elecs.at(secElec)->PT > muonloose.at(leadMuon)->PT){
                    eeEvents++;
                    isDielec = true;
                    histoNumEvents->Fill(2);
                }
                // UU if both muons are higher PT than leading electron
                else if(muonloose.at(secMuon)->PT > elecs.at(leadElec)->PT){
                    uuEvents++;
                    isDimuon = true;
                    histoNumEvents->Fill(3);
                }
                // EU otherwise
                else{
                    euEvents++;
                    isEMuon = true;
                    histoNumEvents->Fill(1);
                }
            }
            // 2+ E and exatly 1 muon
            // EU if lone muon is larger PT than second electron
            else if(muonloose.at(leadMuon)->PT > elecs.at(secElec)->PT){
                euEvents++;
                isEMuon = true;
                histoNumEvents->Fill(1);
            }
            // EE if lone muon is smaller PT than both electrons
            else{
                eeEvents++;
                isDielec = true;
                histoNumEvents->Fill(2);
            }
        }
        // Check for 2+ U (and therefore exactly 1 E)
        else if(muonInd.size() >= 2){
            // EU if lone electron is larger PT than second muon
            if(elecs.at(leadElec)->PT > muonloose.at(secMuon)->PT){
                euEvents++;
                isEMuon = true;
                histoNumEvents->Fill(1);
            }
            // UU if lone electron is smaller PT than both muons
            else{
                uuEvents++;
                isDimuon = true;
                histoNumEvents->Fill(3);
            }
        }
        else{
            continue;
        }
        //std::cout << "eventno: "    << eventno  << std::endl;    
        //std::cout << "leadElec: "   << leadElec << std::endl;
        //std::cout << "secElec: "    << secElec  << std::endl;
        //std::cout << "leadMuon: "   << leadMuon << std::endl;
        //std::cout << "secMuon: "    << secMuon  << std::endl;
        //std::cout << "eeEvents: "   << eeEvents << std::endl;
        //std::cout << "uuEvents: "   << uuEvents << std::endl;
        //std::cout << "euEvents: "   << euEvents << std::endl << std::endl;


        totalDileptonEvents++;
        
        // Check for opposing charge leptons
        if(isDielec){
            if((elecs.at(leadElec)->Charge > 0) == (elecs.at(secElec)->Charge > 0))
                continue;
        }
        else if(isDimuon){
            if((muonloose.at(leadMuon)->Charge > 0) == (muonloose.at(secMuon)->Charge > 0))
                continue;
        }
        else if(isEMuon){
            if((elecs.at(leadElec)->Charge > 0) == (muonloose.at(leadMuon)->Charge > 0))
                continue;
        }


        // Invariant Mass Cut
        TLorentzVector l1;
        TLorentzVector l2;
    
        if(isDielec){
            l1.SetPtEtaPhiM(elecs.at(leadElec)->PT,elecs.at(leadElec)->Eta,elecs.at(leadElec)->Phi,0.);
            l2.SetPtEtaPhiM(elecs.at(secElec)->PT,elecs.at(secElec)->Eta,elecs.at(secElec)->Phi,0.);
        }
        else if(isDimuon){
            l1.SetPtEtaPhiM(muonloose.at(leadMuon)->PT,muonloose.at(leadMuon)->Eta,muonloose.at(leadMuon)->Phi,0.);
            l2.SetPtEtaPhiM(muonloose.at(secMuon)->PT,muonloose.at(secMuon)->Eta,muonloose.at(secMuon)->Phi,0.);
        }
        else if(isEMuon){
            l1.SetPtEtaPhiM(elecs.at(leadElec)->PT,elecs.at(leadElec)->Eta,elecs.at(leadElec)->Phi,0.);
            l2.SetPtEtaPhiM(muonloose.at(leadMuon)->PT,muonloose.at(leadMuon)->Eta,muonloose.at(leadMuon)->Phi,0.);
        }
        
        TLorentzVector ll = l1 + l2;

        if(ll.M() < 20)
          continue;
        //invMass++;      


        ////Dielectron and Dimuon specific cuts
        if(isDielec || isDimuon){
          if(ll.M()>76 && ll.M()<106){
              continue;
          }
        }
        invMass++;

        //Jet PT and Eta Cut
        for(size_t i=0;i<jet.size();i++){
            if(jet.at(i)->PT > 30 && jet.at(i)->Eta > -2.4 && jet.at(i)->Eta < 2.4){
                jetInd.push_back(i);
            }
        }
        
        // Jet Multiplicity Cut
        if(jetInd.size()<2){
            continue;
        }
        jetMulti++;

        bool cutAtMET = false;
        if(isDielec || isDimuon){
            for(size_t i=0;i<met.size();i++){
                if(met.at(i)->MET < 40 && !cutAtMET){
                    cutAtMET = true;
                }
            }
        }
        if(cutAtMET)
            continue;
        metCut++;

        // Check if >=1 jets have the BTag
        bool hasBTag = false;

        for(size_t i=0;!hasBTag && i<jetInd.size();i++)
            if(jet.at(jetInd.at(i))->BTag)
                hasBTag = true;

        if(!hasBTag)
          continue;

        bTag++;
                
        // Fill Muon Histograms
        if(isDimuon || isEMuon){
           histoMuonPT->Fill(muonloose.at(leadMuon)->PT);
           histoMuonEta->Fill(muonloose.at(leadMuon)->Eta);
           histoMuonPhi->Fill(muonloose.at(leadMuon)->Phi);

            if(isDimuon){
                histoMuonPTuu->Fill(muonloose.at(leadMuon)->PT);     
                histoMuonEtauu->Fill(muonloose.at(leadMuon)->Eta);
                histoMuonPhiuu->Fill(muonloose.at(leadMuon)->Phi);
            }
            else{
                histoMuonPTeu->Fill(muonloose.at(leadMuon)->PT);     
                histoMuonEtaeu->Fill(muonloose.at(leadMuon)->Eta);
                histoMuonPhieu->Fill(muonloose.at(leadMuon)->Phi);
            }
        }
        // Fill Electron Histograms
        if(isDielec || isEMuon){
            histoElecPT->Fill(elecs.at(leadElec)->PT);
            histoElecEta->Fill(elecs.at(leadElec)->Eta);
            histoElecPhi->Fill(elecs.at(leadElec)->Phi);

            if(isDielec){
                histoElecPTee->Fill(elecs.at(leadElec)->PT);
                histoElecEtaee->Fill(elecs.at(leadElec)->Eta);
                histoElecPhiee->Fill(elecs.at(leadElec)->Phi);
            }
            else{
                histoElecPTeu->Fill(elecs.at(leadElec)->PT);
                histoElecEtaeu->Fill(elecs.at(leadElec)->Eta);        
                histoElecPhieu->Fill(elecs.at(leadElec)->Phi);       
            }
        } 
        // Fill Jet Histograms
        for(size_t i=0;i<jetInd.size();i++){
            histoJetPT->Fill(jet.at(jetInd.at(i))->PT);
            histoJetEta->Fill(jet.at(jetInd.at(i))->Eta);
            histoJetPhi->Fill(jet.at(jetInd.at(i))->Phi);
            numJets++;

            if(isDielec){
                histoJetPTee->Fill(jet.at(jetInd.at(i))->PT);
                histoJetEtaee->Fill(jet.at(jetInd.at(i))->Eta);
                histoJetPhiee->Fill(jet.at(jetInd.at(i))->Phi);
                numJetsee++;
            }
            else if(isEMuon){
                histoJetPTeu->Fill(jet.at(jetInd.at(i))->PT);
                histoJetEtaeu->Fill(jet.at(jetInd.at(i))->Eta);
                histoJetPhieu->Fill(jet.at(jetInd.at(i))->Phi);
                numJetseu++;
            }
            else{
                histoJetPTuu->Fill(jet.at(jetInd.at(i))->PT);
                histoJetEtauu->Fill(jet.at(jetInd.at(i))->Eta);
                histoJetPhiuu->Fill(jet.at(jetInd.at(i))->Phi);
                numJetsuu++;
            }
        
        }

        // MET PT Cut and Fill MET Histograms
        for(size_t i=0;i<met.size();i++){
            histoMET->Fill(met.at(i)->MET);
            histoMETPhi->Fill(met.at(i)->Phi);

            if(isDielec){
                histoMETee->Fill(met.at(i)->MET);
                histoMETPhiee->Fill(met.at(i)->Phi);

            }
            else if(isEMuon){
                histoMETeu->Fill(met.at(i)->MET);
                histoMETPhieu->Fill(met.at(i)->Phi);

            }
            else{
                histoMETuu->Fill(met.at(i)->MET);
                histoMETPhiuu->Fill(met.at(i)->Phi);

            }
        }
        
        histoNumJet->Fill(numJets);

        if(isDimuon)
            histoNumJetuu->Fill(numJetsuu);
        else if(isDielec)
            histoNumJetee->Fill(numJetsee);
        else
            histoNumJeteu->Fill(numJetseu);

    }

    //Print number of events of each type
    std::string eventBreakdownS = "Type of Event\tNumber of Events\n";
    eventBreakdownS += "Events Processed\t";
    eventBreakdownS += std::to_string(numEventsCount);
    eventBreakdownS += "\n";
    eventBreakdownS += "Lepton PT-Eta Cut\t\t";
    eventBreakdownS += std::to_string(totalDileptonEvents);
    eventBreakdownS += "\n";
    eventBreakdownS += "ee\t\t\t";
    eventBreakdownS += std::to_string(eeEvents);
    eventBreakdownS += "\n";
    eventBreakdownS += "uu\t\t\t";
    eventBreakdownS += std::to_string(uuEvents);
    eventBreakdownS += "\n";
    eventBreakdownS += "eu\t\t\t";
    eventBreakdownS += std::to_string(euEvents);
    eventBreakdownS += "\n";
    eventBreakdownS += "invMass\t\t\t";
    eventBreakdownS += std::to_string(invMass);
    eventBreakdownS += "\n";
    eventBreakdownS += "jetMulti\t\t";
    eventBreakdownS += std::to_string(jetMulti);
    eventBreakdownS += "\n";
    eventBreakdownS += "MET\t\t\t";
    eventBreakdownS += std::to_string(metCut);
    eventBreakdownS += "\n";
    eventBreakdownS += "bTag\t\t\t";
    eventBreakdownS += std::to_string(bTag);
    eventBreakdownS += "\n";


    std::cout << eventBreakdownS;

    /*
    * Must be called in the end, takes care of thread-safe writeout and
    * call-back to the parent process
    */
    processEndFunction();
}



void ttbarC::postProcess(){
    /*
    * This function can be used to analyse the output histograms, e.g. extract a signal contribution etc.
    * The function can also be called directly on an output file with the histograms, if
    * RunOnOutputOnly = true
    * is set in the analyser's config file
    *
    * This function also represents an example of how the output of the analyser can be
    * read-back in an external program.
    * Just include the sampleCollection.h header and follow the procedure below
    *
    */

    /*
    * Here, the input file to the extraction of parameters from the histograms is the output file
    * of the parallelised analysis.
    * The sampleCollection class can also be used externally for accessing the output consistently
    */
    d_ana::sampleCollection samplecoll;
    samplecoll.readFromFile(getOutPath());

    std::vector<TString> alllegends = samplecoll.listAllLegends();

    /*
    * Example how to process the output.
    * Usually, one would define the legendname of the histogram to be used here
    * by hand, e.g. "signal" or "background".
    * To make this example run in any case, I am using alllegends.at(0), which
    * could e.g. be the signal legend.
    *
    * So in practise, the following would more look like
    * samplecoll.getHistos("signal");
    */
    if(alllegends.size()>0){
        d_ana::histoCollection histos=samplecoll.getHistos(alllegends.at(0));

        /*
        * here, the histogram created in the analyze() function is selected and evaluated
        * The histoCollection maintains ownership (you don't need to delete the histogram)
        */
        //const TH1* myplot=histos.getHisto("histoname1");

        //std::cout << "(example output): the integral is " << myplot->Integral() <<std::endl;

        /*
        * If the histogram is subject to changes, please clone it and take ownership
        */

        //TH1* myplot2=histos.cloneHisto("histoname1");

        /*
        * do something with the histogram
        */

        //delete myplot2;
    }

    /*
    * do the extraction here.
    */



}



