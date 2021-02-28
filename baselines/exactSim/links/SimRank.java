package links;

import java.util.*;

import util.Config;


public class SimRank {
	public static class NPComparator implements Comparator<NodesPair> {

		public int compare(NodesPair one, NodesPair two) {
			return Double.compare(one.val, two.val);
		}
	}
	public static class NodesPair{
		public int n1;
		public int n2;
		public double val;
		public NodesPair(int node1, int node2, double v){
			n1 = node1;
			n2 = node2;
			val = v;
		}
	}
	/** The value for the SimRank dampening factor */
	private double dampening = Config.alpha;

	/** The data structure containing the Web linkage graph */
	private WebGraph graph;

	/** A <code>Map</code> containing the SimRank values for each page */
	private Map<Integer, Map<Integer, Double>> scores;

	/** 
	 * Constructor for SimRank
	 * 
	 * @param graph The data structure containing the Web linkage graph
	 */
	public SimRank(WebGraph graph) {
		this.graph = graph;
		this.scores = new HashMap<Integer, Map<Integer, Double>>();
		int numLinks = graph.numNodes();
		Double faux = new Double(1 / graph.numNodes());
		for (int i = 0; i < numLinks; i++) {
			HashMap<Integer, Double> aux = new HashMap<Integer, Double>();
			for (int j = 0; j < i; j++)
				aux.put(new Integer(j), new Double(-1));
			scores.put(new Integer(i), aux);
		}
		//System.out.println("The initial sm matrix: "+scores);
	}

	/**
	 * Sets the value for the SimRank dampening factor. The amount of SimRank that
	 * is transferred depends on a dampening factor which stands for â€œthe probability 
	 * that a random surfer will get boredâ€�. The dampening factor generally is set to 0.85.
	 * 
	 * @param damp The dampening factor
	 */
	public void setDampening(double damp) {
		this.dampening = damp;
	}

	/**
	 * Returns the dampening factor used for the SimRank Algorithm. The amount of SimRank that
		* is transferred depends on a dampening factor which stands for â€œthe probability 
		* that a random surfer will get boredâ€�. The dampening factor generally is set to 0.85.
	 * 
	 * @return The dampening factor
	 */
	public double getDampening() {
		return this.dampening;
	}

	/**
	 * Computes the SimRank value for all the nodes in the Web Graph.
	 * In this method, the number of iterations of the algorithm is set accordingly to
	 * the number of nodes in the Web graph.
	 *
	 */
	public void computeSimRank() {
		int n = graph.numNodes();
		int iter = Config.depth;
		computeSimRank(iter);
	}

	/**
	 * Computes the SimRank value for all the nodes in the Web Graph.
	 * The prodcedure can be
	 * found on the article <a href="http://www-cs-students.stanford.edu/~glenj/simrank.pdf">SimRank: A Measure of Structural-Context Similarity</a>.
	 *
	 * @param iter The number of iterations for the algorithm
	 * 
	 */
	public void computeSimRank(int iter) {
		Double score = null;
		int numLinks = graph.numNodes();
		for (int i = 0; i < numLinks; i++) {
			HashMap aux = new HashMap();
			for (int j = 0; j < i; j++) aux.put(new Integer(j), new Double(0));
			scores.put(new Integer(i), aux);
		}
	//System.out.println("Matrix before iteration:" +scores);
		while ((iter--) > 0) {
			Map<Integer, Map<Integer, Double>> newScores = new HashMap<Integer, Map<Integer, Double>>();
			int numInLinks1 = 0;
			int numInLinks2 = 0;
			for (int id1 = 0; id1 < numLinks; id1++) {
		//		System.out.println("===Node1 is"+id1);
				Map<Integer, Double> map3 = (Map<Integer, Double>) (scores.get(new Integer(id1)));
				//System.out.println("map3 (scores of) of "+ id1 + "is: "+ map3);
				Map map1 = graph.inLinks(new Integer(id1));
				numInLinks1=map1.size();
			//	System.out.println("inlinks and weights of " +id1 +" is: "+ map1);
				for (int id2 = 0; id2 < id1; id2++) {
					Map map3_2 = (Map) (newScores.get(new Integer(id2)));
					if (map3_2 == null){
						map3_2 = (Map) (scores.get(new Integer(id2))); 
						newScores.put(new Integer(id1), map3_2);
					}
			//		System.out.println("======Node2="+ id2);
					Map map2 = graph.inLinks(new Integer(id2));
					numInLinks2=map2.size();
			//		System.out.println("inlinks and weights of " +id2 +" is: "+ map2);
					
					score = new Double(0);
					//boolean first = false;
					Iterator it1 = map1.keySet().iterator();
					while (it1.hasNext()) {
						Iterator it2 = map2.keySet().iterator();
						Integer link1 = (Integer)(it1.next());
				//		System.out.println("one inlink of" +id1 + " is: "+ link1 );
						//Double weight1 = (Double)(map1.get(link1));
						//if(weight1!=null && weight1.doubleValue()>0) numInLinks1++;
						while (it2.hasNext()) {
							Integer link2 = (Integer)(it2.next());
					//		System.out.println("one inlink of" +id2 + " is: "+ link2 );
							//Double weight2 = (Double)(map2.get(link2));
							//if(weight2!=null && weight2.doubleValue()>0) {
							//	if(weight1!=null && weight1.doubleValue()>0)	{
							//		numInLinks2++;
									score = new Double(simRank(link1,link2).doubleValue()+score.doubleValue());		
				//					System.out.println("after adding the old value of ("+ link1 +", "+ link2+"), the sum ="+score );
							//	}
															
							//	if(first) numInLinks2++;
							} 
						}							
					//	first = true;	
				//	System.out.println("numInlinks1 and numInlinks2 "+ numInLinks1+" "+ numInLinks2);
					score = new Double(( dampening / ( numInLinks1 * numInLinks2 ) ) * score.doubleValue() );								
					map3.put(new Integer(id2), score);
					map3_2.put(new Integer(id1), score);
				//	System.out.println("new value of "+id1 + " "+ id2+ "is: " + score);
					
				//	System.out.println("======Finish " +id1+" "+ id2);
					}
					
					
				newScores.put(new Integer(id1), map3);	
					
				}
				
			//	System.out.println("newScores of"+ id1 +" is: "+ newScores.get(id1) );
			//System.out.println("newScores: "+ newScores);
			for (int j = 0; j < numLinks; j++) {
				scores.put(new Integer(j), newScores.get(new Integer(j)));
			}
		//	System.out.println("Matrix after iteration: " +iter+ " is: "+scores);
			
		}
	}

	/**
	 * Returns the SimRank score between a given link and all other links in the Web graph
	 * 
	 * @param link The url for the link
	 * @return A Map with the Amsler score between the given link and all other
		 *         links in the Web graph. Keys in the Map are link identifyers for all the other links,
		 *         and values correspond to the Amsler score
	 */
	public Map simRank(String link) {
		return simRank(graph.getIdbyString(link));
	}

	/**
	 * Returns the SimRank score between two given links
	 * 
	 * @param link1 The url for one of the links
	 * @param link2 The url for the other link
	 * @return The Amsler score between the two given links
	 */
	public Double simRank(String link1, String link2) {
		return simRank(
			graph.getIdbyString(link1),
			graph.getIdbyString(link2));
	}

	/**
	 * Returns the SimRank score between a given link identifyer and all other links in the Web graph
	 * Identifyers are Integer numberes, used in <code>WebGraph</code> to
	 * represent the Web graph for efficiency reasons.
	 * 
	 * @param link The identifyer for the link
	 * @return A Map with the Amsler score between the given link and all other
		 *         links in the Web graph. Keys in the Map are link identifyers for all the other links,
		 *         and values correspond to the Amsler score
	 */
	private Map simRank(Integer id) {
//		if (id.intValue() != 0) {
//			if (((Integer) (((Map) (scores.get(id))).get(new Integer(0))))
//				.doubleValue()
//				< 0) {
//				computeSimRank();
//				return simRank(id);
//			}
//		} else {
//			if (((Integer) (((Map) (scores.get(new Integer(1))))
//				.get(new Integer(0))))
//				.doubleValue()
//				< 0) {
//				computeSimRank();
//				return simRank(id);
//			}
//		}
		return (Map) (scores.get(id));
	}

	/**
	 * Returns the SimRank score between two given link identifyers
	 * Identifyers are Integer numberes, used in <code>WebGraph</code> to
	 * represent the Web graph for efficiency reasons.
		 *
	 * @param link1 The identifyer for one of the links
	 * @param link2 The identifyer for the other link
	 * @return The Amsler score between the two given link identifyers
	 * @see WebGraph.IdentifyerToURL()
	 */
	private Double simRank(Integer id1, Integer id2) {
		if (id1.equals(id2))
			return new Double(1);
	//	System.out.println("id1;id2: "+ id1 +" "+ id2);
		if (id2.intValue() > id1.intValue()) {
			Integer id3 = id1;
			id1 = id2;
			id2 = id3;
		}
	
		Double aux = (Double) (((Map) (scores.get(id1))).get(id2));
	//	System.out.println("Get old value of "+id1 +" "+id2+"= "+aux);
		if (aux.intValue() < 0) {
			System.out.println("value < 0");
			computeSimRank();
			return simRank(id1, id2);
		}
		return aux;
	}
	public PriorityQueue<NodesPair> topK(int k){
		NPComparator  npc = new NPComparator();
		PriorityQueue<NodesPair> H = new PriorityQueue<NodesPair>(k, npc);
		for (Integer i : scores.keySet()){
			Map<Integer, Double> map_i = scores.get(i);
			for (Integer j : map_i.keySet()){
				if (i < j){
					double val_i_j = map_i.get(j);
					if (H.size() < k){
						H.add(new NodesPair(i, j, val_i_j));
					}
					else if (val_i_j > H.peek().val){
						H.poll();
						H.add(new NodesPair(i, j, val_i_j));
					}
				}
			}
			
		}
		return H;
	}
}
