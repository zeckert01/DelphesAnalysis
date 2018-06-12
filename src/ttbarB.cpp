/*
 * ttbarB.cpp
 *
 *  Created on: 24 Aug 2016
 *      Author: jkiesele
 */

#include "interface/ttbarB.h"
#include <string>
#include "TObjString.h"

void ttbarB::analyze(size_t childid /* this info can be used for printouts */){

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

	TH1* histoNumJet = addPlot(new TH1D("NumJet","Number of Jets",30,0.5,30.5),"Jets","N_{e}");
	//TH1* histoNumVert = addPlot(new TH1D("NumVert","Number of Vertices",100,0,100),"Vertices","N_{e}");
	TH1* histoNumEvents = addPlot(new TH1D("NumEvents","Number of Events by Type",4,-0.5,4));

	/*
	 * If (optionally) a skim or a flat ntuple is to be created, please use the following function to initialize
	 * the tree.
	 * The output files will be written automatically, and a config file will be created.
	 */
	//TTree* myskim=addTree();
	TTree* eventBreakdown=addTree();
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


		histoNumEvents->Fill(0);
		/*
		 * Begin the event-by-event analysis
		 */
		/*for(size_t i=0;i<elecs.size();i++){
			histo->Fill(elecs.at(i)->PT);
		}
		*/
		int numJets = 0;

		bool isDimuon = false;
		bool isDielec = false;
		bool isEMuon = false;
		int numElecs = 0;
		int numMuon = 0;
		for(size_t i=0;i<elecs.size();i++){
			if(elecs.at(i)->PT > 20 && elecs.at(i)->Eta < 2.2){
				numElecs++;
			}
		}
		
		for(size_t i=0;i<muonloose.size();i++){
			if(muonloose.at(i)->PT > 20 && muonloose.at(i)->Eta < 2.4){
				numMuon++;
			}
		}

		if(numElecs == 1 && numMuon == 1){
			euEvents++;
			isEMuon = true;
			histoNumEvents->Fill(1);
		}
		else if(numElecs == 2){
			eeEvents++;
			isDielec = true;
			histoNumEvents->Fill(2);
		}
		else if(numMuon == 2){
			uuEvents++;
			isDimuon = true;
			histoNumEvents->Fill(3);
		}
		else
			continue;
		/*
		if(elecs.size() == 1 && muonloose.size() == 1){
			euEvents++;
			isEMuon = true;
		}
		else if(elecs.size() == 2){
			eeEvents++;
			isDielec = true;
		}
		else if(muonloose.size() == 2){
			uuEvents++;
			isDimuon = true;
		}
		else
			continue;
		*/
		if(isDimuon || isEMuon){
			for(size_t i=0;i<muonloose.size();i++){
				if(muonloose.at(i)->PT > 20 && muonloose.at(i)->Eta < 2.4 && muonloose.at(i)->Eta > -2.4){
					histoMuonPT->Fill(muonloose.at(i)->PT);
					histoMuonEta->Fill(muonloose.at(i)->Eta);
					histoMuonPhi->Fill(muonloose.at(i)->Phi);
				}
				else
					continue;
			}
		}
		if(isDielec || isEMuon){
			for(size_t i=0;i<elecs.size();i++){
				if(elecs.at(i)->PT > 20 && elecs.at(i)->Eta < 2.2 && elecs.at(i)->Eta > -2.2){
					histoElecPT->Fill(elecs.at(i)->PT);
					histoElecEta->Fill(elecs.at(i)->Eta);
					histoElecPhi->Fill(elecs.at(i)->Phi);
				}
				else
					continue;
			}
		}
		totalDileptonEvents++;
		for(size_t i=0;i<jet.size();i++){
			if(jet.at(i)->PT > 30 && jet.at(i)->Eta < 2.4 && jet.at(i)->Eta > -2.4){
				histoJetPT->Fill(jet.at(i)->PT);
				histoJetEta->Fill(jet.at(i)->Eta);
				histoJetPhi->Fill(jet.at(i)->Phi);
				numJets++;
			}
		}
		for(size_t i=0;i<met.size();i++){
			if(met.at(i)->MET > 20){
				histoMET->Fill(met.at(i)->MET);
				histoMETPhi->Fill(met.at(i)->Phi);
			}
		}
		
		histoNumJet->Fill(numJets);

		//histoNumVert->Fill(vert.size());	
		

	
		/*
		bool isDilepton = false;
		if(elecs.size() == 1 && muonloose.size() == 1){
			euEvents++;
			isDilepton = true;
			if(elecs.at(0)->PT > 20){
				histoElecPT->Fill(elecs.at(0)->PT);
				histoElecEta->Fill(elecs.at(0)->Eta);
				histoElecPhi->Fill(elecs.at(0)->Phi);
			}
			if(muonloose.at(0)->PT > 20){
				histoMuonPT->Fill(muonloose.at(0)->PT);
				histoMuonEta->Fill(muonloose.at(0)->Eta);
				histoMuonPhi->Fill(muonloose.at(0)->Phi);
			}
		}
		else if(elecs.size() ==2){
			eeEvents++;
			isDilepton = true;
			for(size_t i=0;i<elecs.size();i++){
				if(elecs.at(i)->PT > 20){
					histoElecPT->Fill(elecs.at(i)->PT);
					histoElecEta->Fill(elecs.at(i)->Eta);
					histoElecPhi->Fill(elecs.at(i)->Phi);
				}
			}
		}
		else if(muonloose.size() == 2){
			uuEvents++;
			isDilepton = true;
			for(size_t i=0;i<muonloose.size();i++){
				if(muonloose.at(i)->PT > 20){
					histoMuonPT->Fill(muonloose.at(i)->PT);
					histoMuonEta->Fill(muonloose.at(i)->Eta);
					histoMuonPhi->Fill(muonloose.at(i)->Phi);
				}
			}
		}
		else
			continue;
		*/


					
		/*
		 * Or to fill the skim
		 */

		/*skimmedelecs.clear();
		for(size_t i=0;i<elecs.size();i++){
			//flat info
			elecPt=elecs.at(i)->PT;
			if(elecs.at(i)->PT < 20) continue;
			//or objects
			skimmedelecs.push_back(*elecs.at(i));
		}

		myskim->Fill();
		*/

		/*==SKIM==
		 * Access the branches of the skim
		 */
		//std::vector<Electron> * skimelecs=electrons.content();
		//for(size_t i=0;i<skimelecs->size();i++){
		//	histo->Fill(skimelecs->at(i).PT);
		//}
	}


	std::string eventBreakdownS = "Type of Event\tNumber of Events\n";
	eventBreakdownS += "Total\t\t";
	eventBreakdownS += std::to_string(nevents);
	eventBreakdownS += "\n";
	eventBreakdownS += "ee\t\t";
	eventBreakdownS += std::to_string(eeEvents);
	eventBreakdownS += "\n";
	eventBreakdownS += "uu\t\t";
	eventBreakdownS += std::to_string(uuEvents);
	eventBreakdownS += "\n";
	eventBreakdownS += "eu\t\t";
	eventBreakdownS += std::to_string(euEvents);
	eventBreakdownS += "\n";
	eventBreakdownS += "From Histo\t";
	eventBreakdownS += std::to_string(histoNumEvents->GetBinContent(1));
	eventBreakdownS += "\n";

	int numEvents = static_cast<int>(nevents);	
	eventBreakdown->Branch("Total Processed",&numEvents);
	eventBreakdown->Branch("ee Events",&eeEvents);
	eventBreakdown->Branch("uu Events",&uuEvents);
	eventBreakdown->Branch("eu Events",&euEvents);

	std::cout << eventBreakdownS;

	//histoNumEvents->Write();
	//TNamed* eventBreakdown = new TNamed("Event Breakdown",eventBreakdownS);	
	/*
	 * Must be called in the end, takes care of thread-safe writeout and
	 * call-back to the parent process
	 */
	processEndFunction();
}



void ttbarB::postProcess(){
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

		//const TH1* plotNumEvents = histos.getHisto("numEvents");

		//TH1* myplot2 = histos.cloneHisto("NumEvents");
		//myplot2->Scale(100000);
		//delete myplot2;		
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



