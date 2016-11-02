package find_if;
import java.util.Iterator;
import java.util.Vector;

public class Find_if implements Matcher<String> { //Apparently you can't implement a generic interface
	public static void main(String[] args){		// if class is not generic
			Vector<String> vec = new Vector();
			for(int i=0;i<1000000;i++){
				vec.add("Hello");
			}
			Iterator itr = vec.iterator();
			
	}
	public void find_if(Iterator it,Matcher match){
		while(it.hasNext()){
			 if(match(it.next().toString())){//Something wrong here
				 System.out.println("Matched");				 
			 }
		}
			
	}

	@Override
	public boolean match(String elem){
		if(elem.equals("Hello")){
		return true;
		}
		return false;
	}
}
