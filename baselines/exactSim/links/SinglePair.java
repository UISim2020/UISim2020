package links;

import java.io.*;
import java.util.*;

import util.*;



public class SinglePair{
	
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
		//sm.computeSimRank(Config.depth);
		long elapsed =  System.currentTimeMillis() - start;
		
	/*	double score  = sm.simRank(args[1], args[2]);
		System.out.println("The simrank score of ("+args[1]+","+args[2]+") is: "+score);
		*/
		
		
		 System.out.println("\nLoading queries...");
	        List<String[]> qids = new ArrayList<String[]>();
	        TextReader in = new TextReader(Config.queryFile);
	        String line;
	        while ( (line = in.readln()) != null) {
	        	String[] parts = line.split("\t");
				String a = parts[0];
				String b = parts[1];
				qids.add(new String[]{a,b});
	        }
	        in.close();
	
	        System.out.println("Starting single-pair query processing...");
	        
	        TextWriter out = new TextWriter(Config.outputDir + "/exact_singleP_C"+Config.alpha+"_D"+Config.depth);       
	        ////
	        
	        for (String[] qid : qids) {
	        	System.out.println("Processing Sim("+qid[0]+","+qid[1]+")");
	        	//Map<Integer, Double> result = new HashMap<Integer, Double>();
	        	
	        	double simScore =sm.simRank(qid[0], qid[1]);
	        	
	        	out.writeln(elapsed+"ms "+simScore);
	           
	        }
	        
	        ////single-source version
	        
	      /*  for (int qid : qids) {
	        	Map<Integer, Double> result = new HashMap<Integer, Double>();
	        	List<Entry<Integer, Double>> rankedResult = null;
	            result = sr.computeResult(qid);
	           
	            
	            rankedResult = MapUtil.sortMap(result,Config.resultTop);
	        
	    
				out.write(elapsed + "ms ");
				double sum =0.0;
				for (Map.Entry<Integer, Double> e : rankedResult){
	                out.write(e.getKey() + "_" + e.getValue() + " ");
	                sum +=e.getValue();
				}
				System.out.println("The sum of vector is: " + sum);
	          
	            out.writeln();*/
	       
	        
	        out.close();
	        System.out.println("End.");
	
	
	}
}