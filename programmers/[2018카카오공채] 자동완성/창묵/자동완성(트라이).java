
import java.util.HashMap;
import java.util.Iterator;


public class Main{


  public static void main(String[] argv){

    String[] words = {"word","war","warrior","world"};
    System.out.println(solution(words));

  }

  public static int solution(String[] words){
    Trie trie = new Trie();
    int result;
    for(int i=0;i<words.length;i++){
      trie.insert(words[i]);
    }
    trie.printTrie(trie.getRoot());
    result=trie.result;

    return result;
  }



}


class Trie{

  private TrieNode root;
  int result;

  public TrieNode getRoot() {
    return root;
  }

  Trie(){

    if(root==null)
      root=new TrieNode();

  }

  void insert(String word){

    HashMap<Character,TrieNode> curMap=this.root.getChildNode();
    TrieNode curNode;
    char subword;

    for(int i=0;i<word.length();i++){
      subword=word.charAt(i);

      if(curMap.containsKey(subword)){ // 이미 존재하는 노드면
          curNode = curMap.get(subword);
          curNode.cnt++;
      }
      else{ // 존재하지 않는 노드이면
        curNode = new TrieNode(); // 새 노드를 생성하여
        if(i==word.length()-1)
          curNode.setLastChar(true);
        curMap.put(subword,curNode); // 현재 map에 insert.
      }

      curMap=curNode.getChildNode();
    }

  }


  void printTrie(TrieNode cur){ // root

    HashMap<Character,TrieNode> curMap=cur.getChildNode(); // root의 map
    Iterator<TrieNode> iterator = curMap.values().iterator();
    TrieNode scanNode;

    while(iterator.hasNext()){ //
      scanNode=iterator.next();
      if(scanNode.cnt==1){
        this.result++;
        continue;
      }
      this.result+=scanNode.cnt;

      if(scanNode.getChildNode()!=null){
        printTrie(scanNode);
      }
    }
  }

}

class TrieNode{
  private HashMap<Character,TrieNode> childNode;
  private boolean isLastChar;
  public int cnt;

  public TrieNode(HashMap<Character, TrieNode> childNode, boolean isLastChar) {
    this.childNode = childNode;
    this.isLastChar = isLastChar;
    this.cnt=1;
  }

  public TrieNode(){
    this.childNode=new HashMap<>();
    this.isLastChar=false;
    this.cnt=1;
  }

  public HashMap<Character, TrieNode> getChildNode() {
    return childNode;
  }

  public void setChildNode(HashMap<Character, TrieNode> childNode) {
    this.childNode = childNode;
  }

  public boolean isLastChar() {
    return isLastChar;
  }

  public void setLastChar(boolean lastChar) {
    isLastChar = lastChar;
  }
}