using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using QPS.NEW.DAL;

namespace QPS.NEW.BLL
{
    public class Room
    {
        private QPS.NEW.DAL.SQLHelper sqlHelper_;

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
                "select ImagePath,Address,Name,Content,RoomPrice,Id from Room where ";

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
    }
}
