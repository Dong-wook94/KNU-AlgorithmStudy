import java.util.HashMap;
import java.util.Map;

public class ProgrammersSkillTree {


    static Map<Character,Boolean> skillMap;
    public static int solution(String skill, String[] skill_trees) {
        int answer = 0;
        skillMap = new HashMap<Character, Boolean>();
        for(String skillTree : skill_trees){
            initSkillMap(skill);
            if(isPossibleSkillTree(skillTree,skill)){
                answer++;
            }
        }


        return answer;
    }

    public static void initSkillMap(String skill) {
        for(int i=0;i<skill.length();i++){
            skillMap.put(skill.charAt(i),false);
        }
    }

    private static boolean isPossibleSkillTree(String skillTree, String skill) {
        int cur=0;
        char curNeedSkill = skill.charAt(cur);
        for(int i=0;i<skillTree.length();i++){
            char c = skillTree.charAt(i);
            if(skillMap.containsKey(c)){
                if(curNeedSkill == c){
                    skillMap.put(c,true);
                    cur++;
                    if(cur<skill.length()) {
                        curNeedSkill = skill.charAt(cur);
                    }

                }
                else{
                    boolean possibleChar = skillMap.get(c);
                    if(!possibleChar){
                        return false;
                    }
                }
            }
        }

        return true;
    }

    public static void main(String[] args) {
        String skill = "CBD";
        String[] skillTrees = {"BACDE","CBADF","AECB","BDA"};
        int result = solution(skill,skillTrees);
        System.out.println(result);
    }
}
