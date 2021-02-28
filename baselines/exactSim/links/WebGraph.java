package links;



// HOST TABLE -> INDEX TABLE(A,B) -> Page TABLE

import java.io.*;
import java.util.*;

import util.Config;
import util.TextReader;

/**
 * This class implements a memory Data Structure for storing graphs.</p><p>
 * 
 * A large amount of research has recently focused on the graph structure (or link structure)
 * of the World Wide Web, which has proven to be extremely useful for improving the
 * performance of search engines and other tools for navigating the web.
 * For example, the Pagerank algorithm of Brin and Page, used in the Google search
 * engine, and the HITS algorithm of Kleinberg both rank pages according to the 
 * number and importance of other pages that link to them.</p><p>
 * 
 * This class provides the methods needed to efficiently compute with graphs and to
 * experiment with such algorithms, using main memory for storage.
 *
 * @author Bruno Martins
 */
public class WebGraph {

	/** A Map storing relationships from numeric identifiers to URLs, usefull for storing Web graphs */
	private Map IdentifyerToURL;
	
	/** A Map storing relationships from URLs to numeric identifiers, usefull for storing Web graphs */
	private Map URLToIdentifyer;

	/**
	 *  A Map storing InLinks. For each identifyer (the key), another Map is stored,
	 *  containing for each inlink an associated "connection weight"
	 */
	private Map InLinks;
	
	/**
	 *  A Map storing OutLinks. For each identifyer (the key), another Map is stored,
	 *  containing for each inlink an associated "connection weight"
	 */
	private Map OutLinks;

	/** The number of nodes in the graph */
	private int nodeCount;

	/**
	 * Constructor for WebGraph
     *
	 */
	public WebGraph () {
		IdentifyerToURL = new HashMap();
		URLToIdentifyer = new HashMap();
		InLinks = new HashMap();
		OutLinks = new HashMap();
		nodeCount = 0;
	}

	/**
	 * Constructor for WebGraph, reading data from a text file. Each line of the file
	 * contains an association in the form: 
	 *
	 *    http://url1.com -> http://url2.com 1.0
	 * 
	 * Stating that "http://url1.com" contains an outlink to "http://url2.com", with 
	 * an associated connection strength of 1.0
	 *
	 * @param aux The name of the file
	 * @throws Exception 
	 */
	public WebGraph (String file) throws Exception {
		this();
	//	BufferedReader reader = new BufferedReader(new FileReader(file));
		 TextReader in = new TextReader(file);
		String line;
		while((line=in.readln())!=null) {
			String[] parts= line.trim().split("\t");
			
			/*int index1 = line.indexOf("->");
			if(index1==-1) addLink(line.trim()); else {
				String url1 = line.substring(0,index1).trim();
				String url2 = line.substring(index1+2).trim();
				Double strength = new Double(1.0);
				index1 = url2.indexOf(" ");
				if(index1!=-1) try {
					strength = new Double(url2.substring(index1+1).trim());
					url2 = url2.substring(0,index1).trim(); 
				} catch ( Exception e ) {}*/
			
				addLink (parts[0],parts[1],1.0);
			}
		in.close();
		
	}
	
	/**
	 * Returns the identifyer associated with a given URL
	 * 
	 * @param URL The URL
	 * @return The identifyer associated with the given URL
	 */
	public Integer getIdbyString ( String URL ) {
		/*String host;
		String name;
		int index = 0 , index2 = 0;
		if(URL.startsWith("http://")) index = 7; 
		else if(URL.startsWith("ftp://")) index = 6;
		index2 = URL.substring(index).indexOf("/");
		if(index2!=-1) {
			name = URL.substring(index+index2+1);
			host = URL.substring(0,index+index2);
		} else {
			host = URL;
			name = "";
		}
		Map map = (Map)(URLToIdentifyer.get(host));
		if(map==null) return null;
		return (Integer)(map.get(name));*/
		
		
		if(URLToIdentifyer.get(URL)==null) return null;
		return (Integer)(URLToIdentifyer.get(URL));
	}

	/**
	 * Returns the URL associated with a given identifyer
	 * 
	 * @param id The identifyer
	 * @return The URL associated with the given identifyer
	 */
	public String getStringbyId ( Integer id ) {
		return (String)(IdentifyerToURL.get(id));
	}
	
	/**
	 *  Adds a node to the graph
	 * 
	 * @param link The URL associated with the added node
	 */
	public void addLink (String link) {
		Integer id = getIdbyString(link);
		if(id==null) {
			id = new Integer(nodeCount);
			nodeCount++;
			/*String host;
			String name;
			int index = 0 , index2 = 0;
			if(link.startsWith("http://")) index = 7; 
			else if(link.startsWith("ftp://")) index = 6;
			index2 = link.substring(index).indexOf("/");
			if(index2!=-1) {
				name = link.substring(index+index2+1);
				host = link.substring(0,index+index2);
			} else {
				host = link;
				name = "";
			}
	
			Map map = (Map)(URLToIdentifyer.get(host));
			if(map==null)map = new HashMap();
			map.put(name,id);
			URLToIdentifyer.put(host,map);
			IdentifyerToURL.put(id,link);
			InLinks.put(id,new HashMap());
			OutLinks.put(id,new HashMap());*/
			URLToIdentifyer.put(link, id);
			IdentifyerToURL.put(id,link);
			InLinks.put(id,new HashMap());
			OutLinks.put(id,new HashMap());
			
		}
	}

	/**
	 * Adds an association between two given nodes in the graph. If the 
	 * corresponding nodes do not exists, this method creates them. If the
	 * connection already exists, the strength value is updated.
	 * 
	 * @param fromLink The URL for the source node in the graph 
	 * @param fromLink The URL for the target node in the graph
	 * @param fromLink The strength to associate with the connection
	 * @return The strength associated with the connection
	 */
	public Double addLink (String fromLink, String toLink, Double weight) {
		addLink(fromLink);
		addLink(toLink);
		Integer id1 = getIdbyString(fromLink);
		Integer id2 = getIdbyString(toLink); 
		return addLink(id1,id2,weight);
	}

	/**
	 * Adds an association between two given nodes in the graph. If the 
	 * corresponding nodes do not exists, this method creates them. If the
	 * connection already exists, the strength value is updated.
	 * 
	 * @param fromLink The identifyer for the source node in the graph 
	 * @param fromLink The identifyer for the target node in the graph
	 * @param fromLink The strength to associate with the connection
	 * @return The strength associated with the connection
	 */
	private Double addLink ( Integer fromLink, Integer toLink, Double weight ) {
	            	Double aux;
		Map map1 = (Map)(InLinks.get(toLink));
		Map map2 = (Map)(OutLinks.get(fromLink));
		aux = (Double)(map1.get(fromLink));
		if(aux==null) map1.put(fromLink,weight); 
		else if(aux.doubleValue()<weight.doubleValue()) map1.put(fromLink,weight); 
		else weight = new Double(aux.doubleValue());
		aux = (Double)(map2.get(toLink));
		if(aux==null) map2.put(toLink,weight);
		else if(aux.doubleValue()<weight.doubleValue()) map2.put(toLink,weight);
		else {
			weight = new Double(aux.doubleValue());
			map1.put(fromLink,weight);
		}
		InLinks.put(toLink,map1);
		OutLinks.put(fromLink,map2);
		return weight;

	}

	/**
	 * Returns a Map of the nodes that connect to a given
	 * node in the graph. Each mapping contains the identifyer for a node
	 * and the associated connection strength.  
	 * 
	 * @param URL The URL for the node in the graph 
	 * @return A Map of the nodes that connect to the given node in the graph.
	 */
	public Map inLinks ( String URL ) {
		Integer id = getIdbyString(URL);
		return inLinks(id);
	}
	
	/**
	 * Returns a Map of the nodes that connect to a given
	 * node in the graph. Each mapping contains the identifyer for a node
	 * and the associated connection strength.  
	 * 
	 * @param link The identifyer for the node in the graph 
	 * @return A Map of the nodes that connect to the given node in the graph.
	 */
	public Map inLinks ( Integer link ) {
		if(link==null) return new HashMap();
		Map aux = (Map)(InLinks.get(link));
		return (aux == null) ? new HashMap() : aux;
	}

	/**
	 * Returns a Map of the nodes that are connected from a given
	 * node in the graph. Each mapping contains the identifyer for a node
	 * and the associated connection strength.  
	 * 
	 * @param URL The URL for the node in the graph 
	 * @return A Map of the nodes that are connected from the given node in the graph.
	 */
	public Map outLinks ( String URL ) {
		Integer id = getIdbyString(URL);
		return outLinks(id);
	}

	/**
	 * Returns a Map of the nodes that are connected from a given
	 * node in the graph. Each mapping contains the identifyer for a node
	 * and the associated connection strength.  
	 * 
	 * @param link The URL for the node in the graph 
	 * @return A Map of the nodes that are connected from the given node in the graph.
	 */
	public Map outLinks ( Integer link ) {
		if(link==null) return new HashMap();
		Map aux = (Map)(OutLinks.get(link));
		return (aux == null) ? new HashMap() : aux;
	}
	
	/**
	 * Returns the connection strength between two nodes, assuming there is a
	 * connection from the first to the second. If no connection exists, a link
	 * strength of zero is returned.
	 * 
	 * @param fromLink The source link
	 * @param toLink  The target link
	 * @return The strenght for the connection between fromLink and toLink ( fromLink -> toLink )
	 * @see inLink
	 */
	public Double inLink ( String fromLink, String toLink ) {
		Integer id1 = getIdbyString(fromLink);
		Integer id2 = getIdbyString(toLink); 
		return inLink(id1,id2);
	}
	
	/**
	 * Returns the connection strength between two nodes, assuming there is a
	 * connection from the first to the second. If no connection exists, a link
	 * strength of zero is returned.
	 * 
	 * @param fromLink The source link
	 * @param toLink  The target link
	 * @return The strenght for the connection between fromLink and toLink ( fromLink -> toLink )
	 * @see outLink
	 */
	public Double outLink ( String fromLink, String toLink ) {
		Integer id1 = getIdbyString(fromLink);
		Integer id2 = getIdbyString(toLink); 
		return outLink(id1,id2);
	}

	/**
	 * Returns the connection strength between two nodes, assuming there is a
	 * connection from the first to the second. If no connection exists, a link
	 * strength of zero is returned.
	 * 
	 * @param fromLink An identifyer for the source link
	 * @param toLink  An identifyer for the target link
	 * @return The strenght for the connection between fromLink and toLink ( fromLink -> toLink )
	 * @see outLink
	 */
	public Double inLink ( Integer fromLink, Integer toLink ) {	
		Map aux = inLinks(toLink);
		if(aux==null) return new Double(0);
		Double weight = (Double)(aux.get(fromLink));
		return (weight == null) ? new Double(0) : weight;
	}
	
    /**
     * Returns the connection strength between two nodes, assuming there is a
     * connection from the first to the second. If no connection exists, a link
     * strength of zero is returned.
     * 
     * @param fromLink An identifyer for the source link
     * @param toLink  An identifyer for the target link
     * @return The strenght for the connection between fromLink and toLink ( fromLink -> toLink )
     * @see inLink
     */
	public Double outLink ( Integer fromLink, Integer toLink ) {	
		Map aux = outLinks(fromLink);
		if(aux==null) return new Double(0);
		Double weight = (Double)(aux.get(toLink));
		return (weight == null) ? new Double(0) : weight;
	}

	/**
	 * Transforms a bi-directional graph to an uni-directional equivalent. The connection
	 * strenght between two nodes A and B that are inter-connected in the bi-directional
	 * graph is transformed into MAX(weight_inlink(A,B),weight_outlink(A,B))
	 */
	public void transformUnidirectional () {
		Iterator it = OutLinks.keySet().iterator();
		while (it.hasNext()) {
			Integer link1 = (Integer)(it.next());
			Map auxMap = (Map)(OutLinks.get(link1));
			Iterator it2 = auxMap.keySet().iterator();
			while (it2.hasNext()) {
				Integer link2 = (Integer)(it.next());
				Double weight = (Double)(auxMap.get(link2));
				addLink(link2,link1,weight);
			}
		}
	}

	/**
	 * Remove nodes which correspond to an internal link. In a Web Graph, internal
	 * links are those made to pages that are situated on the same host.
	 */
	public void removeInternalLinks () {
		int index1;
		Iterator it = OutLinks.keySet().iterator();
		while (it.hasNext()) {
			Integer link1 = (Integer)(it.next());
			Map auxMap = (Map)(OutLinks.get(link1));
			Iterator it2 = auxMap.keySet().iterator();
			if(it2.hasNext()) {
				String URL1 = (String)(IdentifyerToURL.get(link1));
				index1 = URL1.indexOf("://");
				if(index1!=-1) URL1=URL1.substring(index1+3);
				index1 = URL1.indexOf("/");
				if(index1!=-1) URL1=URL1.substring(0,index1);
				while (it2.hasNext()) {
					Integer link2 = (Integer)(it.next());
					String URL2 = (String)(IdentifyerToURL.get(link2));
					index1 = URL2.indexOf("://");
					if(index1!=-1) URL2=URL1.substring(index1+3);
					index1 = URL2.indexOf("/");
					if(index1!=-1) URL2=URL1.substring(0,index1);
					if(URL1.equals(URL2)) {
						auxMap.remove(link2);
						OutLinks.put(link1,auxMap);
						auxMap = (Map)(InLinks.get(link2));
						auxMap.remove(link1);
						InLinks.put(link2,auxMap);
					}
				}
			}
		}
	}
	
	/**
	 *  Remove nodes which correspond to nepotistic links. In a Web Graph, nepotistic
	 *  links are tipically those made to pages that are situated on the same host, correspondig
	 *  to links made for hypertext navigational purposes rather than semantic similarity.
	 *
	 *  See the paper "<a href="http://www.cse.lehigh.edu/~brian/pubs/2000/aaaiws/">Recognizing Nepotistic Links on the Web</a>" by Brian Davison, presented at the 
	 *  AAAI-2000 Workshop on Artificial Intelligence for Web Search, Austin, TX, July 30, and published in Artificial Intelligence for Web Search,
	 *  Technical Report WS-00-01, pp. 23-28, AAAI Press.
	 * 
	 */
	public void removeNepotistic() {
		removeInternalLinks();
	}

	/**
	 * Remove nodes which correspond to stop URLs. 
	 * 
	 * @param stopURLs An array of Strings with the Stop URLs
	 */
	public void removeStopLinks(String stopURLs[]) {
		HashMap aux = new HashMap();
		for (int i=0; i<stopURLs.length; i++) aux.put(stopURLs[i],null);
		removeStopLinks(aux);
	}
	
	/**
	 * Remove nodes which correspond to stop URLs. In a Web Graph, stop URLs
	 * correspond to very frequent pages. A link from/to such an URLs usually does not
	 * imply semantic similarity.
	 * 
	 * @param stopURLs A Map where keys are the Stop URLs
	 */
	public void removeStopLinks(Map stopURLs) {
		int index1;
		Iterator it = OutLinks.keySet().iterator();
		while (it.hasNext()) {
			Integer link1 = (Integer)(it.next());
			String URL1 = (String)(IdentifyerToURL.get(link1));
			index1 = URL1.indexOf("://");
			if(index1!=-1) URL1=URL1.substring(index1+3);
			index1 = URL1.indexOf("/");
			if(index1!=-1) URL1=URL1.substring(0,index1);
			if(stopURLs.containsKey(URL1)) {
				OutLinks.put(link1,new HashMap());
				InLinks.put(link1,new HashMap());
			}
		}
	}

	/**
	 * Returns the number of nodes in the graph
	 * 
	 * @return The number of nodes in the graph
	 */
	public int numNodes() {
		return nodeCount;
	}

}
