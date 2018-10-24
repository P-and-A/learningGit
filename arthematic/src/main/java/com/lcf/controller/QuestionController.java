package com.lcf.controller;

import com.lcf.service.IQuestionService;
import org.apache.ibatis.annotations.Param;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

/**
 * @author liaochaofan
 * @date 2018/10/18 20:23
 */
@Controller

public class QuestionController {
    @Autowired
    private IQuestionService iQuestionService;

    @RequestMapping(value = "get_questions/{num}")
    @ResponseBody
    public String getAllQuestion(@PathVariable("num")int num){
        return iQuestionService.getAllQuestion(num);
    }

}
