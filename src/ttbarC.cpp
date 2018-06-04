/*
 * ttbarC.cpp
 *
 *  Created on: 24 Aug 2016
 *      Author: jkiesele
 */

#include "interface/ttbarC.h"
#include <string>
#include "TObjString.h"

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

	TH1* histoElecPT = addPlot(new TH1D("ElecPT","Electron PT",200,0,200),"p_{T} [GeV]","N_{e}");
	TH1* histoElecEta = addPlot(new TH1D("ElecEta","Electron Eta",100,-3,3),"Eta", "N_{e}");
	TH1* histoElecPhi = addPlot(new TH1D("ElecPhi","Electron Phi",100,-3,3),"Phi", "N_{e}");


	TH1* histoMuonPT = addPlot(new TH1D("MuonPT","Muon PT",200,0,200),"p_{T} [GeV]","N_{e}");
	TH1* histoMuonEta = addPlot(new TH1D("MuonEta","Muon Eta",100,-3,3),"Eta", "N_{e}");
	TH1* histoMuonPhi = addPlot(new TH1D("MuonPhi","Muon Phi",100,-3,3),"Phi", "N_{e}");
	
	TH1* histoMET = addPlot(new TH1D("METPT","MET PT",200,0,200),"p_{T} [GeV]","N_{e}");
	TH1* histoMETPhi = addPlot(new TH1D("METPhi","MET Phi",100,-3,3),"Phi", "N_{e}");

	TH1* histoNumJet = addPlot(new TH1D("NumJet","Number of Jets",30,0,30),"Jets","N_{e}");

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
	
	//size_t nevents=tree()->entries();
	size_t nevents = 100000;
	
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

		histoNumEvents->Fill(0);
		
		
		int numJets = 0;
		
		bool isDimuon = false;
		bool isDielec = false;
		bool isEMuon = false;

		// execute electron, muon, and jet PT Cuts
		std::vector<size_t> eleInd;
		std::vector<size_t> muonInd;
		std::vector<size_t> jetInd;
		if(elecs.size()>0){
			for(size_t i=0;i<elecs.size();i++){
				if(elecs.at(i)->PT > 20){
					eleInd.push_back(i);
				}
			}
		}
		
		for(size_t i=0;i<muonloose.size();i++){
			if(muonloose.at(i)->PT > 20){	
				muonInd.push_back(i);
			}
		}
		
		for(size_t i=0;i<jet.size();i++){
			if(jet.at(i)->PT > 30){
				jetInd.push_back(i);
			}
		}
		
		// Jet Multiplicity Cut
		if(jetInd.size()<2){
			continue;
		}
		jetMulti++;

		// Check if >=1 jets have the BTag
		//bool hasBTag = false;
		//if(!jetInd.size()){
		//	for(size_t i=0;!hasBTag && jetInd.size();i++)
		//		if(jet.at(jetInd.at(i))->BTag)
		//			hasBTag = true;
		//}	
		//if(!hasBTag)
		//	continue;
		//bTag++;
				
		//Find Leading and Next to leading electron and muon
		int leadElec = 0;
                int secElec = 1;

                int leadMuon = 0;
                int secMuon = 1;

                //if(elecs.size() >= 2){
                //        for(size_t i=1;i<elecs.size();i++){
                //                if(elecs.at(i)->PT > elecs.at(leadElec)->PT){
                //                        secElec = leadElec;
                //                        leadElec = i;
                //                }
                //                else if(elecs.at(i)->PT > elecs.at(secElec)->PT)
                //                        secElec = i;
                //        }
                //}

                //if(muonloose.size() >= 2){
                //        for(size_t i=1;i<muonloose.size();i++){
                //                if(muonloose.at(i)->PT > muonloose.at(leadMuon)->PT){
                //                        secMuon = leadMuon;
                //                        leadMuon = i;
                //                }
                //                else if(muonloose.at(i)->PT > muonloose.at(secMuon)->PT)
                //                        secMuon = i;
                //        }
                //}	
		//

		// determine dilepton type
	
		if(eleInd.size() == 1 && muonInd.size() == 1){
			euEvents++;
			isEMuon = true;
			histoNumEvents->Fill(1);
		}
		else if(eleInd.size() == 2){
			eeEvents++;
			isDielec = true;
			histoNumEvents->Fill(2);
		}
		else if(muonInd.size() == 2){
			uuEvents++;
			isDimuon = true;
			histoNumEvents->Fill(3);
		}
		else
			continue;

		totalDileptonEvents++;
		// Invariant Mass Cut
		TLorentzVector l1;
		TLorentzVector l2;
	
		if(isDielec){
			l1.SetPtEtaPhiM(elecs.at(leadElec)->PT,elecs.at(leadElec)->Eta,elecs.at(leadElec)->Phi,0.);
			l2.SetPtEtaPhiM(elecs.at(secElec)->PT,elecs.at(secElec)->Eta,elecs.at(secElec)->Phi,0.);
		}
		else if(isDimuon){
			l1.SetPtEtaPhiM(elecs.at(leadMuon)->PT,elecs.at(leadMuon)->Eta,elecs.at(leadMuon)->Phi,0.);
			l2.SetPtEtaPhiM(muonloose.at(secMuon)->PT,muonloose.at(secMuon)->Eta,muonloose.at(secMuon)->Phi,0.);
		}
		else if(isEMuon){
			l1.SetPtEtaPhiM(elecs.at(leadElec)->PT,elecs.at(leadElec)->Eta,elecs.at(leadElec)->Phi,0.);
			l2.SetPtEtaPhiM(muonloose.at(leadMuon)->PT,muonloose.at(leadMuon)->Eta,muonloose.at(leadMuon)->Phi,0.);
		}
		
		TLorentzVector ll = l1 + l2;

		if(ll.M() < 20)
			continue;
		invMass++;		


		//Dielectron and Dimuon specific cuts
		if(isDielec || isDimuon){
			if(ll.M()>76 && ll.M()<106){
				continue;
			}
			for(size_t i=0;i<met.size();i++){
				if(met.at(i)->MET < 40){
					continue;
				}
			}
		}
		
		// Fill Muon Histograms
		if(isDimuon || isEMuon){
			for(size_t i=0;i<muonInd.size();i++){
	
				histoMuonPT->Fill(muonloose.at(muonInd.at(i))->PT);
				histoMuonEta->Fill(muonloose.at(muonInd.at(i))->Eta);
				histoMuonPhi->Fill(muonloose.at(muonInd.at(i))->Phi);
				}
		}

		// Fill Electron Histograms
		if(isDielec || isEMuon){
			for(size_t i=0;i<eleInd.size();i++){
				histoElecPT->Fill(elecs.at(eleInd.at(i))->PT);
				histoElecEta->Fill(elecs.at(eleInd.at(i))->Eta);
				histoElecPhi->Fill(elecs.at(eleInd.at(i))->Phi);
				
			}
		}

		
		
		// Fill Jet Histograms
		for(size_t i=0;i<jetInd.size();i++){
			histoJetPT->Fill(jet.at(jetInd.at(i))->PT);
			histoJetEta->Fill(jet.at(jetInd.at(i))->Eta);
			histoJetPhi->Fill(jet.at(jetInd.at(i))->Phi);
			numJets++;
		
		}

		// MET PT Cut and Fill MET Histograms
		for(size_t i=0;i<met.size();i++){
			histoMET->Fill(met.at(i)->MET);
			histoMETPhi->Fill(met.at(i)->Phi);
		}
		
		histoNumJet->Fill(numJets);
	}

	//Print number of events of each type
	std::string eventBreakdownS = "Type of Event\tNumber of Events\n";
	eventBreakdownS += "Total Dilepton\t\t";
	eventBreakdownS += std::to_string(totalDileptonEvents);
	eventBreakdownS += "\n";
	eventBreakdownS += "jetMulti\t\t\t";
	eventBreakdownS += std::to_string(jetMulti);
	eventBreakdownS += "\n";
	eventBreakdownS += "bTag\t\t\t";
	eventBreakdownS += std::to_string(bTag);
	eventBreakdownS += "\n";
	eventBreakdownS += "invMass\t\t\t";
	eventBreakdownS += std::to_string(invMass);
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



