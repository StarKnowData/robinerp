using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Configuration;

namespace QPS.NEW.DAL
{
    public class SQLHelper
    {
        private string connectString_;
        private static SqlConnection SQLCONN = null;

        public SQLHelper(string connectString)
        {
            if (connectString == null || connectString == "")
            {
                connectString_ = ConfigurationSettings.AppSettings["dbConnString"].ToString();
            }
            else
            {
                connectString_ = connectString;
            }
        }


        public SqlConnection Connection()
        {
            SqlConnection conn = null;

            if (SQLCONN == null)
            {
                try
                {
                    SQLCONN = new SqlConnection(connectString_);
                    conn = SQLCONN;
                }
                catch (Exception e)
                {
                    conn = null;
                    SQLCONN = null;
                }

            }
            else
            {
                conn = SQLCONN;
            }
            return conn;
        }


        public bool OpenConnection(SqlConnection conn)
        {
            bool res = true;

            try
            {
                if (conn.State != ConnectionState.Open)
                {
                    conn.Open();
                }
            }
            catch(Exception e)
            {
                CloseConnection(conn);

                conn = Connection();
                if (conn.State != ConnectionState.Open)
                {
                    conn.Open();
                }
            }

            return res;
        }


        public void CloseConnection(SqlConnection conn)
        {
            try
            {
                if (conn.State != ConnectionState.Closed)
                {
                    conn.Close();
                    conn.Dispose();
                }
            }
            catch(Exception e)
            {
                // do nothing
            }
        }




        /// <summary>
        /// 判断某个表中是否存在某个列
        /// </summary>
        /// <param name="tableName">表名</param>
        /// <param name="columnName">列名</param>
        /// <returns></returns>
        public bool ExistsColumn(string tableName, string columnName)
        {
            string sqlstr = string.Format("select count(1) from syscolumns where [id]=object_id('{0}') and [name]='{1}'", tableName, columnName);
            return Convert.ToInt32(GetSingle(sqlstr, CommandType.Text, null)) > 0;
        }




        /// <summary>
        /// 判断某个表是否存在
        /// </summary>
        /// <param name="tableName">表名</param>
        /// <returns></returns>
        public bool ExistsTable(string tableName)
        {
            string sqlstr = string.Format("select count(1) from sysobjects where id = object_id(N'[{0}]') and OBJECTPROPERTY(id, N'IsUserTable') = 1", tableName);
            return Convert.ToInt32(GetSingle(sqlstr, CommandType.Text, null)) > 0;
        }



        /// <summary>
        /// 执行SQL语句或存储过程，返回首行首列,例如获取总行数等操作
        /// </summary>
        /// <param name="commtype">命令类型SQL语句或存储过程</param>
        /// <param name="commtxt">命令内容</param>
        /// <param name="parameters">命令参数</param>
        /// <returns>查询结果首行首列</returns>
        public object GetSingle(string commtxt, CommandType commtype, params SqlParameter[] parameters)
        {
            object res = null;
            try
            {
                SqlConnection Conn = Connection();
                if(Conn!=null)
                {
                    using (SqlCommand Comm = new SqlCommand())
                    {
                        InitCommand(Comm, commtxt, commtype, Conn, parameters);
                        if(OpenConnection(Conn))
                        {
                            res = Comm.ExecuteScalar();
                        }

                    }
                }
            }
            catch (SqlException E)
            {
                res = null;
            }

            return res;
        }




        /// <summary>
        /// 执行SQL语句或存储过程，返回受影响行数，如用于增删改操作
        /// </summary>
        /// <param name="commtype">命令类型SQL语句或存储过程</param>
        /// <param name="commtxt">命令内容</param>
        /// <param name="parameters">命令参数</param>
        /// <returns>返回受影响行数</returns>
        public int ExecuteCommand(string commtxt, CommandType commtype, params SqlParameter[] parameters)
        {
            int res = -1;
            try
            {
                SqlConnection Conn = Connection();
                if(Conn!=null)
                {
                    using (SqlCommand Comm = new SqlCommand())
                    {
                        InitCommand(Comm, commtxt, commtype, Conn, parameters);
                        if(OpenConnection(Conn))
                        {
                            res = Comm.ExecuteNonQuery();                            
                        }
                    }
                }

            }
            catch (SqlException E)
            {
                res = -1;
            }

            return res;
        }



        /// <summary>
        /// 执行SQL语句或存储过程，返回DataSet
        /// </summary>
        /// <param name="commtype">命令类型SQL语句或存储过程</param>
        /// <param name="commtxt">命令内容</param>
        /// <param name="parameters">命令参数</param>
        /// <returns>查询结果集</returns>
        public DataSet GetDataSet(string commtxt, CommandType commtype, params SqlParameter[] parameters)
        {
            DataSet dataset = new DataSet();
            try
            {
                SqlConnection Conn = Connection();
                if(Conn!=null)
                {
                    using (SqlCommand Comm = new SqlCommand())
                    {
                        InitCommand(Comm, commtxt, commtype, Conn, parameters);
                        using (SqlDataAdapter Adapter = new SqlDataAdapter(Comm))
                        {
                            if(OpenConnection(Conn))
                            {
                                Adapter.Fill(dataset);                                
                            }

                        }
                    }
                }
            }
            catch (SqlException E)
            {
                dataset = null;
            }

            return dataset;
        }




        /// <summary>
        /// 执行SQL语句或存储过程，返回DataTable
        /// </summary>
        /// <param name="commtype">命令类型SQL语句或存储过程</param>
        /// <param name="commtxt">命令内容</param>
        /// <param name="parameters">命令参数</param>
        /// <returns>查询结果集</returns>
        public DataTable GetDataTable(string commtxt, CommandType commtype, params SqlParameter[] parameters)
        {
            DataTable dt = new DataTable();
            try
            {
                dt = GetDataSet(commtxt, commtype, parameters).Tables[0];
            }
            catch (SqlException E)
            {
                dt = null;
            }

            return dt;
        }




        /// <summary>
        /// 执行SQL语句或存储过程，返回DataReader对象
        /// </summary>
        /// <param name="commtype">命令类型SQL语句或存储过程</param>
        /// <param name="commtxt">命令内容</param>
        /// <param name="parameters">命令参数</param>
        /// <returns>返回DataReader对象</returns>
        public SqlDataReader GetDataReader(string commtxt, CommandType commtype, params SqlParameter[] parameters)
        {
            SqlDataReader reader = null;

            SqlConnection Conn = Connection();
            if(Conn!=null)
            {
                SqlCommand Comm = new SqlCommand();
                InitCommand(Comm, commtxt, commtype, Conn, parameters);
                
                if(OpenConnection(Conn))
                {
                    reader = Comm.ExecuteReader(CommandBehavior.CloseConnection); 
                }

            }


            return reader;
        }



        /// <summary>
        /// 事务处理，批执行SQL命令
        /// </summary>
        /// <param name="sqls">SQL命令</param>
        /// <returns></returns>
        public bool ExecuteSqlTransaction(params string[] sqlstrs)
        {
            bool res = false;
            try
            {
                SqlConnection Conn = Connection();
                if(Conn!=null)
                {
                    using (SqlCommand Comm = new SqlCommand())
                    {
                        Comm.Connection = Conn;
                        Conn.Open();
                        SqlTransaction Tran = Conn.BeginTransaction();//开始事务
                        try
                        {
                            Comm.Transaction = Tran;
                            foreach (string sqlstr in sqlstrs)
                            {
                                Comm.CommandText = sqlstr;
                                Comm.ExecuteNonQuery();
                            }
                            Tran.Commit();//提交事务
                            res = true;
                        }
                        catch
                        {
                            Tran.Rollback();//回滚
                            res = false;
                        }
                    }
                }
            }
            catch (SqlException E)
            {
                res = false;
            }

            return res;
        }




        /// <summary>
        /// 初始化SqlCommand对象
        /// </summary>
        /// <param name="comm">SqlCommand对象</param>
        /// <param name="commtype">命令类型SQL语句或存储过程</param>
        /// <param name="parameters">命令参数</param>
        private void InitCommand(SqlCommand comm, string commtxt, CommandType commtype, SqlConnection conn, params SqlParameter[] parameters)
        {
            comm.CommandText = commtxt;
            comm.CommandType = commtype;
            comm.Connection = conn;

            if (parameters != null)
            {
                foreach (SqlParameter parameter in parameters)
                {
                    if (parameter != null)
                    {
                        comm.Parameters.Add(parameter);
                    }
                }
            }
        }
    }
}