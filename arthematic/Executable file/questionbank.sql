/*
Navicat MySQL Data Transfer

Source Server         : mysql
Source Server Version : 50534
Source Host           : localhost:3306
Source Database       : questionbank

Target Server Type    : MYSQL
Target Server Version : 50534
File Encoding         : 65001

Date: 2018-10-24 16:06:55
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for q_a
-- ----------------------------
DROP TABLE IF EXISTS `q_a`;
CREATE TABLE `q_a` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `question` varchar(255) NOT NULL,
  `ans` varchar(50) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=27 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of q_a
-- ----------------------------
INSERT INTO `q_a` VALUES ('1', '5+76*2', '157');
INSERT INTO `q_a` VALUES ('2', '8*8+9', '73');
INSERT INTO `q_a` VALUES ('3', '7*7-5', '42');
INSERT INTO `q_a` VALUES ('4', '5*4+5', '25');
INSERT INTO `q_a` VALUES ('5', '(1+1)*（-5）', '-10');
INSERT INTO `q_a` VALUES ('6', '55*10+2', '552');
INSERT INTO `q_a` VALUES ('7', '(55-5)/2', '25');
INSERT INTO `q_a` VALUES ('8', '78+2/5', '78.4');
INSERT INTO `q_a` VALUES ('9', '67+（-3）*11', '34');
INSERT INTO `q_a` VALUES ('10', '(88+12)/50', '500');
INSERT INTO `q_a` VALUES ('11', '77+23-50', '50');
INSERT INTO `q_a` VALUES ('12', '99*10-5', '985');
INSERT INTO `q_a` VALUES ('13', '5+78/2', '44');
INSERT INTO `q_a` VALUES ('14', '78+5*2', '88');
INSERT INTO `q_a` VALUES ('15', '45+45*2', '135');
INSERT INTO `q_a` VALUES ('16', '88+50/(-2)', '63');
INSERT INTO `q_a` VALUES ('17', '3!', '6');
INSERT INTO `q_a` VALUES ('18', '5!', '120');
INSERT INTO `q_a` VALUES ('19', '(48+2)/2', '25');
INSERT INTO `q_a` VALUES ('20', '66+55/(-5)', '55');
INSERT INTO `q_a` VALUES ('21', '7!', '5040');
INSERT INTO `q_a` VALUES ('22', '85+96+64+75', '320');
INSERT INTO `q_a` VALUES ('23', '78+(45/3)*2', '108');
INSERT INTO `q_a` VALUES ('24', '275/5+85/5', '72');
INSERT INTO `q_a` VALUES ('25', '46+78*54', '4258');
INSERT INTO `q_a` VALUES ('26', '8!', '40 320');
