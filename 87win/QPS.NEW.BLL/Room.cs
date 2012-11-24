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
            bool res = false;

            string[] filedName = new string[50];
            string[] paramName = new string[50];
            SqlParameter[] sqlParams = new SqlParameter[50];
            int Count = 0;

            if (model.Id == -999)
                return false;

            if (model.Id != -999)
            {
                filedName[Count] = "Id";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Id);
                Count++;
            }
            if (model.Name != null)
            {
                filedName[Count] = "Name";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Name);
                Count++;
            }
            if (model.RoomType != null)
            {
                filedName[Count] = "RoomType";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.RoomType);
                Count++;
            }
            if (model.RoomPrice != -999)
            {
                filedName[Count] = "RoomPrice";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.RoomPrice);
                Count++;
            }
            if (model.Are != null)
            {
                filedName[Count] = "Are";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Are);
                Count++;
            }
            if (model.Address != null)
            {
                filedName[Count] = "Address";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Address);
                Count++;
            }
            if (model.ImagePath != null)
            {
                filedName[Count] = "ImagePath";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.ImagePath);
                Count++;
            }
            if (model.Content != null)
            {
                filedName[Count] = "Content";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Content);
                Count++;
            }
            if (model.RoomState != -999)
            {
                filedName[Count] = "RoomState";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.RoomState);
                Count++;
            }
            if (model.OwnerID != -999)
            {
                filedName[Count] = "OwnerID";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.OwnerID);
                Count++;
            }
            if (model.IfRecommend != -999)
            {
                filedName[Count] = "IfRecommend";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.IfRecommend);
                Count++;
            }
            if (model.Examine != -999)
            {
                filedName[Count] = "IfExamine";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Examine);
                Count++;
            }
            if (model.RecommendTime != null)
            {
                filedName[Count] = "RecommendTime";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.RecommendTime);
                Count++;
            }

            StringBuilder strSql = new StringBuilder();
            strSql.Append("update Room set ");
            for (int i = 1; i < Count; i++)
            {
                strSql.Append(filedName[i]);
                strSql.Append("=");
                strSql.Append(paramName[i]);
                if (i != Count - 1)
                {
                    strSql.Append(",");
                }
            }
            strSql.Append(" where ");
            strSql.Append(filedName[0] + "=" + paramName[0]);


            int num = Convert.ToInt32(sqlHelper_.ExecuteCommand(
                strSql.ToString(),
                CommandType.Text,
                sqlParams
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


        public int Add(QPS.NEW.Model.Room model)
        {
                string strSql = "";
                strSql += "insert into Users(Name,RoomType,RoomPrice,Are,Address,ImagePath,Content,RoomState,OwnerID,IfRecommend,IfExamine) ";
                strSql += "values(@Name,@RoomType,@RoomPrice,@Are,@Address,@ImagePath,@Content,@RoomState,@OwnerID,@IfRecommend,@IfExamine)";

                int res = -1;
                res = sqlHelper_.ExecuteCommand(
                    strSql,
                    CommandType.Text,
                    new System.Data.SqlClient.SqlParameter[]
                {
                    new SqlParameter("@Name",model.Name),
                    new SqlParameter("@RoomType",model.RoomType),
                    new SqlParameter("@RoomPrice",model.RoomPrice),
                    new SqlParameter("@Are",model.Are),
                    new SqlParameter("@Address",model.Address),
                    new SqlParameter("@ImagePath",model.ImagePath),
                    new SqlParameter("@Content",model.Content),
                    new SqlParameter("@RoomState",model.RoomState),
                    new SqlParameter("@OwnerID",model.OwnerID),
                    new SqlParameter("@IfRecommend",model.IfRecommend),
                    new SqlParameter("@IfExamine",model.Examine)
                }
                    );

                if (res != 1)
                {
                    throw new Exception("Error:写入数据库失败");
                }

            return 1;
        }


        public List<QPS.NEW.Model.Room> GetModelList(string strWhere)
        {
            List<QPS.NEW.Model.Room> list = new List<Model.Room>();
            QPS.NEW.Model.Room room = new Model.Room();

            DataTable dt = sqlHelper_.GetDataTable(
               "select * from Room where " + strWhere,
               CommandType.Text,
                null
               );

            if (dt != null)
            {
                for (int i = 0; i < dt.Rows.Count; i++)
                {
                    room.Id = Convert.ToInt32(dt.Rows[i]["Id"]);
                    room.Name = dt.Rows[i]["Name"].ToString();
                    room.RoomType = dt.Rows[i]["RoomType"].ToString();
                    room.RoomPrice = Convert.ToDecimal(dt.Rows[i]["RoomPrice"]);
                    room.Are = dt.Rows[i]["Are"].ToString();
                    room.Address = dt.Rows[i]["Address"].ToString();
                    room.ImagePath = dt.Rows[i]["ImagePath"].ToString();
                    room.Content = dt.Rows[i]["Content"].ToString();
                    room.RoomState = Convert.ToInt32(dt.Rows[i]["RoomState"]);
                    room.OwnerID = Convert.ToInt32(dt.Rows[i]["OwnerID"]);
                    room.IfRecommend = Convert.ToInt32(dt.Rows[i]["IfRecommend"]);
                    room.Examine = Convert.ToInt32(dt.Rows[i]["Examine"]);

                    if (dt.Rows[i]["RecommendTime"] == DBNull.Value)
                        room.RecommendTime = null;
                    else
                        room.RecommendTime = dt.Rows[i]["RecommendTime"].ToString();

                    list.Add(room);
                }
            }

            return list;
        }

        public bool Delete(int roomId)
        {
            bool res = false;
            int num =
                sqlHelper_.ExecuteCommand(
                "delete from Room where Id=@Id",
                CommandType.Text,
                new SqlParameter[]
                {
                    new SqlParameter("@Id",roomId)
                }
                );
            if (num == 1)
                res = true;

            return res;
        }
    }
}
