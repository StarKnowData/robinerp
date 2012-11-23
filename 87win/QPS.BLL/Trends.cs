using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using QPS.NEW.DAL;

namespace QPS.NEW.BLL
{
    public class Trends
    {
        private QPS.NEW.DAL.SQLHelper sqlHelper_;

        public Trends()
        {
            sqlHelper_ = new SQLHelper(null);
        }

        public DataSet GetTopList(int num)
        {
            DataSet ds = null;
            string strsql = "select top 6 Id,Title,time from Trends";

            ds = sqlHelper_.GetDataSet(strsql,CommandType.Text,null);

            return ds;
        }

        public DataSet GetList()
        {
            DataSet ds = null;
            string strsql = "select Id,Title,time from Trends";

            ds = sqlHelper_.GetDataSet(strsql, CommandType.Text, null);

            return ds;
        }

        public DataSet GetList(string strWhere)
        {
            DataSet ds = null;
            string strsql = "select Title,time Content from Trends where ";

            strsql += strWhere;

            ds = sqlHelper_.GetDataSet(strsql, CommandType.Text, null);

            return ds;
        }
    }
}
