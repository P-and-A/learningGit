package com.lcf.pojo;

/**
 * @author liaochaofan
 * @date 2018/10/18 20:15
 */
public class Question {
    String question;
    String ans;

    public Question(String question, String ans) {
        this.question = question;
        this.ans = ans;
    }

    public String getQuestion() {
        return question;
    }

    public void setQuestion(String question) {
        this.question = question;
    }

    public String getAns() {
        return ans;
    }

    public void setAns(String ans) {
        this.ans = ans;
    }
}
