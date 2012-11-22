using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Configuration;


public class SQLHelper
{
    private string connectString_;


    public SQLHelper(string connectString)
    {
        connectString_ = connectString;
    }


    public SqlConnection Connection()
    {
        try
        {
            return new SqlConnection(connectString_);
        }
        catch (SqlException E)
        {
            throw E;
        }
    }


    public void OpenConnection(SqlConnection conn)
    {
        if (conn.State != ConnectionState.Open)
        {
            conn.Open();
        }
    }


    public void CloseConnection(SqlConnection conn)
    {
        if (conn.State != ConnectionState.Closed)
        {
            conn.Close();
            conn.Dispose();
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
        try
        {
            using (SqlConnection Conn = Connection())
            {
                using (SqlCommand Comm = new SqlCommand())
                {
                    InitCommand(Comm, commtxt, commtype, Conn, parameters);
                    OpenConnection(Conn);
                    return Comm.ExecuteScalar();
                }
            }
        }
        catch (SqlException E)
        {
            throw E;
        }
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
            using (SqlConnection Conn = Connection())
            {
                using (SqlCommand Comm = new SqlCommand())
                {
                    InitCommand(Comm, commtxt, commtype, Conn, parameters);
                    OpenConnection(Conn);
                    res = Comm.ExecuteNonQuery();

                    return res;
                }
            }
        }
        catch (SqlException E)
        {
            throw E;
        }
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
        try
        {
            DataSet dataset = new DataSet();

            using (SqlConnection Conn = Connection())
            {
                using (SqlCommand Comm = new SqlCommand())
                {
                    InitCommand(Comm, commtxt, commtype, Conn, parameters);
                    using (SqlDataAdapter Adapter = new SqlDataAdapter(Comm))
                    {
                        OpenConnection(Conn);
                        Adapter.Fill(dataset);
                    }
                }
            }
            return dataset;
        }
        catch (SqlException E)
        {
            throw E;
        }
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
        try
        {
            return GetDataSet(commtxt, commtype, parameters).Tables[0];
        }
        catch (SqlException E)
        {
            throw E;
        }
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
        SqlConnection Conn = Connection();
        SqlCommand Comm = new SqlCommand();
        InitCommand(Comm, commtxt, commtype, Conn, parameters);
        OpenConnection(Conn);

        SqlDataReader reader = Comm.ExecuteReader(CommandBehavior.CloseConnection);

        return reader;
    }



    /// <summary>
    /// 事务处理，批执行SQL命令
    /// </summary>
    /// <param name="sqls">SQL命令</param>
    /// <returns></returns>
    public bool ExecuteSqlTransaction(params string[] sqlstrs)
    {
        try
        {
            using (SqlConnection Conn = Connection())
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
                        return true;
                    }
                    catch
                    {
                        Tran.Rollback();//回滚
                        return false;
                    }
                }
            }
        }
        catch (SqlException E)
        {
            throw E;
        }
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
