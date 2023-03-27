import json
import re


class Lesson:
	def __init__(self, session):
		self.session = session
		self.lesson_id = []
		self.email = None
		print("")
		print("请输入您想要查询的老师")
		self.teacher_name = input()
		self.headers = {
			'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/99.0.4844.51 Safari/537.36'
		}
		self.POOL = ["241", "221", "202", "201", "181", "161", "141", "121", "101", "81", "62", "61", "39", "35", "23", "38", "20", "43", "21", "34", "42", "37", "17", "41", "18", "33", "22", "9", "19", "40", "36", "32", "10", "24", "44", "25", "11", "47", "46", "45", "27", "51", "50", "12", "26", "49", "48", "8", "7", "31", "6", "16", "5", "30", "4", "15", "3", "29", "2", "1", "14", "28", "53", "52", "13"]

	def get_lesson_id(self):
		sn = \
			re.findall("\d+",
					   self.session.get("https://jw.ustc.edu.cn/for-std/lesson-search", headers=self.headers).url)[0]

		params = {
			"teacherNameLike": self.teacher_name,
		}
		for p in self.POOL:
			source = "https://jw.ustc.edu.cn/for-std/lesson-search/semester/{}/search/{}".format(p, sn)
			rsp = self.session.get(source, headers=self.headers, params=params)
			result = json.loads(rsp.content.decode("utf-8"))
			if len(result["data"]) == 0:
				continue
			for course in result["data"]:
				course_id = course["id"]
				teachers = course["teacherAssignmentList"]
				teachers = [teacher["person"]["nameZh"] for teacher in teachers] + [teacher["person"]["nameEn"] for teacher in teachers]
				if self.teacher_name in teachers:
					self.lesson_id.append(course_id)
					break
			else:
				continue
			break

	def find_all(self):
		self.get_lesson_id()
		email_list = dict()
		for tid in self.lesson_id:
			params = {
				"lessonId": tid,
			}
			url = "https://jw.ustc.edu.cn/ws/course-adjustment-apply/get-teacher-info"
			rsp = self.session.get(url, headers=self.headers, params=params)
			pairs = json.loads(rsp.content.decode("utf-8"))
			for s in pairs:
				email_list = email_list | s
		result = []
		if self.teacher_name in email_list:
			result.append("{}老师的邮箱是{}".format(self.teacher_name, email_list[self.teacher_name]))
		else:
			result.append("未找到{}的邮箱".format(self.teacher_name))
		return result

	def find_parms(self):
		sn = \
			re.findall("\d+",
					   self.session.get("https://jw.ustc.edu.cn/for-std/lesson-search", headers=self.headers).url)[0]

		params = {
			"teacherNameLike": self.teacher_name,
		}
		parm = 0
		for p in self.POOL:
			source = "https://jw.ustc.edu.cn/for-std/lesson-search/semester/{}/search/{}".format(p, sn)
			rsp = self.session.get(source, headers=self.headers, params=params)
			result = json.loads(rsp.content.decode("utf-8"))
			if len(result["data"]) == 0:
				parm = parm + 1
				continue
			else:
				break
		parms = []
		if parm:
			parms.append("{}老师最近%d学期未开设课程".format(self.teacher_name) % parm)
		else:
			parms.append("{}老师本学期有开设课程".format(self.teacher_name))
		return parms
