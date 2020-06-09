import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.StringTokenizer;



public class Baekjoon7432 {

    static int numOfDir;
    static Tree tree ;


    public static void main(String[] args) throws IOException {
        inputData();

    }

    public static void inputData() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        numOfDir = Integer.parseInt(br.readLine());
        tree = new Tree();
        TreeNode root = tree.getRoot();
        ArrayList<String> inputString = new ArrayList<>();
        for(int i=0;i<numOfDir;i++){
            String str = br.readLine();
            String s = str.replaceAll("\\\\"," ");
            inputString.add(s);
        }
        Collections.sort(inputString);

        for(String str : inputString){
            //System.out.println(str);
            StringTokenizer st = new StringTokenizer(str," ");
            ArrayList<String> paths = getDirPath(st);
            tree.insertNewDirectory(paths,0,root);
        }
        tree.printTree(root,-1);

    }

    public static ArrayList<String> getDirPath(StringTokenizer st) {
        ArrayList<String> paths = new ArrayList<String>();
        while(st.hasMoreTokens()){
            paths.add(st.nextToken());
        }
        return paths;
    }

    static class TreeNode{
        private int level;
        private String directoryName;
        private ArrayList<TreeNode> child;

        public TreeNode(int level){
            this.level = level;
            this.child = new ArrayList<>();
        }
        public TreeNode(int level, String directoryName) {
            this.level = level;
            this.directoryName = directoryName;
            this.child = new ArrayList<TreeNode>();
        }
        public TreeNode getLastChildNode(){
            int childSize = child.size();
            return child.get(childSize-1);
        }
    }

    static class Tree{
        TreeNode root;

        public Tree() {
            root = new TreeNode(-1);
            this.root = root;
        }

        public TreeNode getRoot() {
            return root;
        }

        public void insertNewDirectory(ArrayList<String> paths, int level, TreeNode curNode){
            if(level>=paths.size())
                return;
            for(TreeNode child : curNode.child){
                if(child.directoryName.equals(paths.get(level))){
                    insertNewDirectory(paths,level+1,child);
                    return;
                }
            }
            //이까지 왔으면 없던 dir
            curNode.child.add(new TreeNode(level,paths.get(level)));
            insertNewDirectory(paths,level+1, curNode.getLastChildNode());
        }

        public void printTree(TreeNode curNode,int level){
            if(curNode.child.isEmpty()){
                printDir(curNode, level);
                return;
            }else{
                if(level!=-1){
                    printDir(curNode, level);
                }
            }
            for(TreeNode child : curNode.child){
                printTree(child,level+1);
            }
        }

        public void printDir(TreeNode curNode, int level) {
            String space = "";
            for (int i = 0; i < level; i++) {
                space += " ";
            }
            System.out.println(space + curNode.directoryName);
        }

    }

}
