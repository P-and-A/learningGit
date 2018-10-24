package com.lcf.service.impl;

import com.lcf.dao.QuestionMapper;
import com.lcf.pojo.Question;
import com.lcf.service.IQuestionService;
import com.lcf.util.ToJsonUtil;
import com.sun.deploy.net.HttpResponse;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.*;

/**
 * @author liaochaofan
 * @date 2018/10/18 20:24
 */
@Service("iQuestionSercive")
public class QuestionService implements IQuestionService{

    @Autowired(required = true)
    private QuestionMapper questionMapper;

    public String getAllQuestion(int num){
        List<Question> questionList = questionMapper.getAllQuestion();
        List<Question> selectList = new ArrayList<>();
        Set<Integer> selected = new HashSet<>();
        int size = questionList.size();
        for(int i=0;i<num;){
            Random random = new Random();
            int randomNum = random.nextInt(size);
            if(selected.add(randomNum)){
                selectList.add(questionList.get(randomNum));
                i++;
            }
        }
        return ToJsonUtil.getToJsonUtil().objectToJson(selectList);
    }
}
