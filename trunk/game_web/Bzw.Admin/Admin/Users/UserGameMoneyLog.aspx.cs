using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using Bzw.Data;
using BCST.Common;
using System.Text;


public partial class Admin_Users_UserGameMoneyLog : AdminBasePage
{
    public string SumMoney;
    protected void Page_Load(object sender, EventArgs e)
    {


        //获取搜索条件
        StringBuilder where = new StringBuilder();
        StringBuilder where1 = new StringBuilder();
        string bd = CommonManager.Web.RequestUrlDecode("bd", "");
        string ed = CommonManager.Web.RequestUrlDecode("ed", "");
        string un = CommonManager.Web.RequestUrlDecode("un", "");
        string type = CommonManager.Web.RequestUrlDecode("ty", "");
        string utype = CommonManager.Web.RequestUrlDecode("uty", "");


        if (!string.IsNullOrEmpty(bd) && CommonManager.String.IsDateTime(bd))
        {
            where1.Append(" and endTime>='" + bd + "'");
        }
        if (!string.IsNullOrEmpty(ed) && CommonManager.String.IsDateTime(ed))
        {
            where1.Append(" and endTime<='" + ed + "'");
        }

        //判断根据用户名还是用户ID
        if (!string.IsNullOrEmpty(un))
        {
            if (type == "byname")
            {
                where.Append(" and UserName='" + un + "'");
            }
            else
            {
                if (CommonManager.String.IsInteger(un))
                {
                    where.Append(" and UserID='" + un + "'");
                }
                else
                {
                    CommonManager.Web.RegJs(this, "alert('" + ChineseMessage.userIdFormatErrorMessage + "')", false);
                }
            }

        }
        //判断是否是根据玩家类别查询,默认真实玩家

        if (!string.IsNullOrEmpty(utype))
        {

            if (utype == "2")
                where.Append(" and isrobot=1 ");
            if (utype == "1")
                where.Append(" and  isrobot=0 ");
        }
        else
        {
            where.Append(" and   isrobot=0 ");
        }


        //绑定记录

        DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
                .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
                .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
                .AddInputParameter("@Columns", DbType.String, "UserID,UserName")
                .AddInputParameter("@TableName", DbType.String, "Tusers")
                .AddInputParameter("@Wheres", DbType.String, where.ToString())
                .AddInputParameter("@KeyName", DbType.String, "UserID")
                .AddInputParameter("@OrderBy", DbType.String, "UserID desc")
                .ToDataSet();

        if (ds.Tables.Count > 0)
        {
            anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
            anpPageIndex.CurrentPageIndex = PageIndex;

            if (ds.Tables[1].Rows.Count > 0)
            {
                rptDataList.Visible = true;
                ltNonData.Visible = false;
                DataTable dt = ds.Tables[1];
                DataColumn dc = new DataColumn();
                dc.ColumnName = "SumMoney";
                dt.Columns.Add(dc);
                foreach (DataRow row in dt.Rows)
                {

                    row["SumMoney"] = DbSession.Default.FromSql("select isnull(sum(ChangeMoney),0)  FROM dbo.Web_vGameRecord  where userid=" + row["UserID"].ToString()+where1 ).ToScalar();

                }
                rptDataList.DataSource = dt;
                rptDataList.DataBind();
                SumMoney = DbSession.Default.FromSql("select isnull(sum(ChangeMoney),0)  FROM dbo.Web_vGameRecord  where userid in (select userid from tusers where 1=1 " + where + ")"+where1).ToScalar().ToString();
            }
            else
            {
                rptDataList.Visible = false;
                ltNonData.Visible = true;
            }
        }
    }
}

