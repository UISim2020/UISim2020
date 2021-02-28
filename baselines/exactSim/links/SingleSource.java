package links;

import java.io.*;
import java.util.*;
import java.util.Map.Entry;

import util.*;



public class SingleSource{
	
	public static void main(String[] args) throws Exception{
		
	//	File file = new File(Config.edgeFile);
	//	System.out.println("file is:"+ Config.edgeFile);
		/*String url1 = "http://url1.com";
		String url2 = "http://url2.com";
		String url3 = "http://url3.com";
		String url4 = "http://url4.com";
		*/
		Config.depth=Integer.valueOf(args[0]);//number of iterations = length of partial tours in consideration
		
		
	/*	Map hubScores= new HashMap();
		Map authorityScores = new HashMap();*/
		long start = System.currentTimeMillis();	
		WebGraph graph = new WebGraph(Config.edgeFile);
	/*	System.out.println("total num. of nodes: "+graph.numNodes());
		System.out.println("Outlinks of U is" + graph.outLinks("U"));
		System.out.println("Outlinks of SA is" + graph.outLinks("SA"));
		System.out.println("Index of U is" + graph.getIdbyString("U"));*/
		SimRank sm = new SimRank(graph);
		
		
		sm.computeSimRank(Config.depth);
		long elapsed =  System.currentTimeMillis() - start;
		
	/*	double score  = sm.simRank(args[1], args[2]);
		System.out.println("The simrank score of ("+args[1]+","+args[2]+") is: "+score);
		*/
		
		
		 System.out.println("\nLoading queries...");
	        List<String> qids = new ArrayList<String>();
	        TextReader in = new TextReader(Config.queryFile);
	        String line;
	        while ( (line = in.readln()) != null) {
	        	
				qids.add(line.trim());
	        }
	        in.close();
	
	        System.out.println("Starting single-source query processing...");
	        
	        TextWriter out = new TextWriter(Config.outputDir + "/exact_singleS_C"+Config.alpha+"_D"+Config.depth);       
	        ////
	        
	       /* for (String[] qid : qids) {
	        	System.out.println("Processing Sim("+qid[0]+","+qid[1]+")");
	        	//Map<Integer, Double> result = new HashMap<Integer, Double>();
	        	
	        	double simScore =sm.simRank(qid[0], qid[1]);
	        	
	        	out.writeln(elapsed+"ms "+simScore);
	           
	        }
	        */
	        ////single-source version
	        
	        for (String qid : qids) {
	        	System.out.println(qid);
	        	Map<Integer, Double> result = new HashMap<Integer, Double>();
	        	result = sm.simRank(qid);
	        	List<util.KeyValuePair> rankedResult = null;
	           
	            
	            rankedResult = sortMap(result,Config.resultTop);
//	            System.out.print(qid);
//            	System.out.print('\t');
//            	System.out.println(result.size());
            	
	    
				out.writeln(elapsed + "ms "+qid+"\t1.0");
				//double sum =0.0;
				for (KeyValuePair e : rankedResult){
	                out.writeln(graph.getStringbyId(e.key) + "\t" + e.value);
	           //     sum +=e.value;
				}
//				System.out.println("The sum of vector is: " + sum);
	          
	            out.writeln();
	       
	        }
	        out.close();
	        System.out.println("End.");
	
	
	}


	private static List<util.KeyValuePair> sortMap(final Map<Integer, Double> result, int k) {
		// TODO Auto-generated method stub
		List<Integer> list = new ArrayList<Integer>(result.keySet().size());
		for (int i : result.keySet())
			list.add(i);
		
		Collections.sort(list, new Comparator<Integer>() {
			@Override
			public int compare(Integer arg0, Integer arg1) {
				return - Double.compare(result.get(arg0), result.get(arg1));
			}} );
		
		if (k > list.size()) 
			k = list.size();
		
		List<KeyValuePair> ranked = new ArrayList<KeyValuePair>(k);

		for (int i = 0; i < k; i++) {
			ranked.add(new KeyValuePair(list.get(i),result.get(list.get(i))));
			
			//add(new KeyValuePair(list.get(i), get(list.get(i))));
		}
		
		return ranked;
	}
	
	
		//System.out.println("@@@@@@@@@@@@@"+map);
		
		

	}