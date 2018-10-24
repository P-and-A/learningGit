package com.lcf.dao;

import com.lcf.pojo.Question;

import java.util.List;

/**
 * @author liaochaofan
 * @date 2018/10/18 20:15
 */
public interface QuestionMapper {
    int getQuestionNum();

    List<Question> getAllQuestion();
}
