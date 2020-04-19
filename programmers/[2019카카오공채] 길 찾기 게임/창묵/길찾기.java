import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;



public class Main{


  public static void main(String argv[]){

    int[][] nodeinfo = {{5,3},{11,5},{13,3},{3,5},{6,1},{1,3},{8,6},{7,2},{2,2}};

    System.out.println(Arrays.deepToString(solution(nodeinfo)));
  }

  public static int[][] solution(int[][] nodeinfo){

    int[][] answer = new int[2][nodeinfo.length];
    BinaryTree BT;
    ArrayList<Node> list;
    ArrayList<Integer> answerTemp;


    list=ArraySort(nodeinfo);
    BT=MakeTree(list);

    BT.preorder(BT.head);
    BT.postorder(BT.head);


    for(int i=0;i<BT.getRes().size();i++){
      answerTemp=BT.getRes().get(i);
      for(int j=0;j<answerTemp.size();j++){
        answer[i][j]=answerTemp.get(j);
      }
    }

    return answer;
  }

  public static ArrayList<Node> ArraySort(int[][] nodeinfo) {

    ArrayList<Node> tempList=new ArrayList<>();

    for(int i=0;i<nodeinfo.length;i++){
      tempList.add(new Node(nodeinfo[i][0],nodeinfo[i][1],i+1));
    }

    Collections.sort(tempList, new Comparator<Node>() {

      @Override
      public int compare(Node node1, Node node2) {
        if (node1.getY() < node2.getY())
          return 1;
        else if (node1.getY() == node2.getY()) {
          if (node2.getX() < node1.getX())
            return 1;
        }

        return -1;
      }
    });

    return tempList;

  }


  public static BinaryTree MakeTree(ArrayList<Node> list){

      BinaryTree BT = new BinaryTree();

      for(int i=0;i<list.size();i++)
        BT.insertNode(list.get(i));

      return BT;

    }

  }


class BinaryTree{

  Node head;
  static ArrayList<ArrayList<Integer>> Res = new ArrayList<>(2);

  BinaryTree(){
    Res.add(new ArrayList<Integer>());
    Res.add(new ArrayList<Integer>());
  }

  public static ArrayList<ArrayList<Integer>> getRes() {
    return Res;
  }

  public void insertNode(Node nNode){

    if(head==null) {
      head=nNode;
      return;
    }

    Node cur=head;
    Node pre;

    while(true) {
      pre=cur;
      if(cur.getX()<nNode.getX()) {
        cur=cur.getRight();
        if(cur==null) {
          pre.setRight(nNode);
          return;
        }
      }
      else {
        cur = cur.getLeft();
        if(cur==null) {
          pre.setLeft(nNode);
          return;
        }
      }
    }

  }

  public static void postorder(Node head){
    if(head!=null){
      postorder(head.getLeft());
      postorder(head.getRight());
      Res.get(1).add(head.getIndexNumber());
    }
  }

  public static void preorder(Node head){
    if(head!=null){
      Res.get(0).add(head.getIndexNumber());
      preorder(head.getLeft());
      preorder(head.getRight());
    }
  }

}

class Node{
   private Node left;
   private Node right;
   private int x;
   private int y;
   private int indexNumber;

  public int getIndexNumber() {
    return indexNumber;
  }

  Node(int x,int y,int indexNumber){
     this.left=null;
     this.right=null;
     this.x=x;
     this.y=y;
     this.indexNumber=indexNumber;
   }

  public Node getLeft() {
    return left;
  }

  public void setLeft(Node left) {
    this.left = left;
  }

  public Node getRight() {
    return right;
  }

  public void setRight(Node right) {
    this.right = right;
  }

  public int getX() {
    return x;
  }

  public int getY() {
    return y;
  }


}
