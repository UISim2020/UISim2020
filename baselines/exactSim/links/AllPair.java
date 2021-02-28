package links;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;

import links.SimRank.NodesPair;
import util.Config;
import util.TextWriter;

public class AllPair {
	public static void main(String[] args) throws Exception{
		Config.depth=Integer.valueOf(args[0]);//number of iterations = length of partial tours in consideration
		int k = Integer.parseInt(args[1]);

		long start = System.currentTimeMillis();	
		System.out.println("Start computing all-pair exact...");
		WebGraph graph = new WebGraph(Config.edgeFile);
	/*	System.out.println("total num. of nodes: "+graph.numNodes());
		System.out.println("Outlinks of U is" + graph.outLinks("U"));
		System.out.println("Outlinks of SA is" + graph.outLinks("SA"));
		System.out.println("Index of U is" + graph.getIdbyString("U"));*/
		SimRank sm = new SimRank(graph);
		
		
		sm.computeSimRank(Config.depth);
		long elapsed =  System.currentTimeMillis() - start;
//            System.out.print(qid);
		TextWriter out = new TextWriter(Config.outputDir + "/" + 
				"Exact-AP-" +  "_D" +Config.depth);		
		
		out.writeln(elapsed + "ms ");
		List<NodesPair> result = new ArrayList();
		PriorityQueue<NodesPair> H = sm.topK(k);
		while (H.size() > 0){
			result.add(H.poll());
		}
		for (int i = result.size() - 1; i >= 0; i--){
			NodesPair npv = result.get(i);
			out.writeln(graph.getStringbyId(npv.n1)+"\t"+graph.getStringbyId(npv.n2)+"\t"+npv.val);
			//System.out.println(graph.getStringbyId(npv.n1)+"\t"+graph.getStringbyId(npv.n2)+"\t"+npv.val);
		}
		out.close();
		System.out.println("End.");
	}
}
