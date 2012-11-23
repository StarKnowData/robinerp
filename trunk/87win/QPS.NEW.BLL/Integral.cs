using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.SqlClient;
using QPS.NEW.DAL;

namespace QPS.NEW.BLL
{
    public class Integral
    {
        private SQLHelper sqlHelper_;

        public Integral()
        {
            sqlHelper_ = new SQLHelper(null);
        }

        public QPS.NEW.Model.Integral GetModel(int Id)
        {
            QPS.NEW.Model.Integral integral = null;
            string strSql = "select * from Integral where Id=@id";

            DataTable dt = sqlHelper_.GetDataTable(
                strSql,
                CommandType.Text,
                new SqlParameter[]
                {
                    new SqlParameter("@id",Id)
                }
                );

            if (dt != null && dt.Rows.Count > 0)
            {
                integral = new Model.Integral();
                integral.Id = Id;
                integral.UserID = dt.Rows[0]["UserID"].ToString();
                integral.Content =Convert.ToInt32( dt.Rows[0]["Content"]);
                integral.CreateTime = Convert.ToDateTime(dt.Rows[0]["CreateTime"]);
                integral.RoomId = Convert.ToInt32(dt.Rows[0]["RoomId"]);
                integral.OrderId = Convert.ToInt32(dt.Rows[0]["OrderId"]);
            }

            return integral;
        }

        public bool Update(QPS.NEW.Model.Integral model)
        {
            string strSql = "";
            bool res = false;

            strSql = "update Integral set UserID=@userid,Content=@content,CreateTime=@createtime,";
            strSql += "RoomId=@roomid,OrderId=@orderid ";
            strSql += " where Id=@id";

            int num = Convert.ToInt32(sqlHelper_.ExecuteCommand(
                strSql,
                CommandType.Text,
                new SqlParameter[]{
                    new SqlParameter("@userid",model.UserID),
                    new SqlParameter("@content",model.Content),
                    new SqlParameter("@createtime",model.CreateTime),
                    new SqlParameter("@roomid",model.RoomId),
                    new SqlParameter("@orderid",model.OrderId),
                    new SqlParameter("@id",model.Id)
                }
                ));
            if (num != 1)
            {
                throw new Exception("Error:更新数据库失败");
            }
            else
            {
                res = true;
            }

            return res;
        }
    }
}
