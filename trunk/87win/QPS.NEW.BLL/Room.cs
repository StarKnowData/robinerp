using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.SqlClient;
using QPS.NEW.DAL;
using QPS.NEW.Model;

namespace QPS.NEW.BLL
{
    public class Room
    {
        private SQLHelper sqlHelper_;

        public Room()
        {
            sqlHelper_ = new SQLHelper(null);
        }

        public DataTable GetDataTableList(string sqlString)
        {
            DataTable dt = null;

            dt=sqlHelper_.GetDataTable(sqlString, CommandType.Text, null);

            return dt;
        }

        public DataSet GetList(string strWhere)
        {
            DataSet ds = null;
            string strSql =
                "select Id,ImagePath,Address,Name,Content,RoomPrice,Content,Are,RoomType from Room where ";

            strSql += strWhere;
            ds = sqlHelper_.GetDataSet(strSql, CommandType.Text, null);

            return ds;
        }

        public DataSet GetAllList(string strWhere)
        {
            DataSet ds = null;
            string strSql =
                "select ImagePath,Address,Name,Content,RoomPrice,Id from Room order by ";

            strSql += strWhere;
            ds = sqlHelper_.GetDataSet(strSql, CommandType.Text, null);

            return ds;
        }


        public QPS.NEW.Model.Room GetModel(int Id)
        {
            QPS.NEW.Model.Room room = null;

            DataTable dt = sqlHelper_.GetDataTable(
                "select * from Room where Id=@id",
                CommandType.Text,
                new System.Data.SqlClient.SqlParameter[]
                {
                    new System.Data.SqlClient.SqlParameter("@id",Id)
                }
                );

            if (dt!=null && dt.Rows.Count > 0)
            {
                room = new Model.Room();

                room.Id = Convert.ToInt32(dt.Rows[0]["Id"]);
                room.Name = dt.Rows[0]["Name"].ToString();
                room.RoomType = dt.Rows[0]["RoomType"].ToString();
                room.RoomPrice = Convert.ToDecimal(dt.Rows[0]["RoomPrice"]);
                room.Are = dt.Rows[0]["Are"].ToString();
                room.Address = dt.Rows[0]["Address"].ToString();
                room.ImagePath = dt.Rows[0]["ImagePath"].ToString();
                room.Content = dt.Rows[0]["Content"].ToString();
                room.RoomState = Convert.ToInt32(dt.Rows[0]["RoomState"]);
                room.OwnerID = Convert.ToInt32(dt.Rows[0]["OwnerID"]);
                room.IfRecommend = Convert.ToInt32(dt.Rows[0]["IfRecommend"]);
                room.Examine = Convert.ToInt32(dt.Rows[0]["IfExamine"]);
                room.RecommendTime = dt.Rows[0]["RecommendTime"].ToString();
            }

            return room;
        }

        public bool Update(QPS.NEW.Model.Room model)
        {
            string strSql = "";
            bool res = false;

            strSql = "update Room set Name=@name,RoomType=@roomtype,RoomPrice=@roomprice,";
            strSql+="Are=@are,Address=@address,ImagePath=@imagepath,Content=@content,";
            strSql+="RoomState=@roomstate,OwnerID=@ownerid,IfRecommend=@ifrecommend,IfExamine=@ifexamine,RecommendTime=@recommendtime ";
            strSql += " where Id=@id";

            int num = Convert.ToInt32(sqlHelper_.ExecuteCommand(
                strSql,
                CommandType.Text,
                new SqlParameter[]{
                    new SqlParameter("@name",model.Name),
                    new SqlParameter("@roomtype",model.RoomType),
                    new SqlParameter("@roomprice",model.RoomPrice),
                    new SqlParameter("@are",model.Are),
                    new SqlParameter("@address",model.Address),
                    new SqlParameter("@imagepath",model.ImagePath),
                    new SqlParameter("@content",model.Content),
                    new SqlParameter("@roomstate",model.RoomState),
                    new SqlParameter("@ownerid",model.OwnerID),
                    new SqlParameter("@ifrecommend",model.IfRecommend),
                    new SqlParameter("@ifexamine",model.Examine),
                    new SqlParameter("@recommendtime",Convert.ToDateTime(model.RecommendTime)),
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
