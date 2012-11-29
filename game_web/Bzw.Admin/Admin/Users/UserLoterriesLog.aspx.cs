using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using BCST.Common;
using System.Text;
using System.Data;
using Bzw.Data;

  public partial class Admin_Users_UserLoterriesLog : AdminBasePage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            //获取搜索条件
            StringBuilder where = new StringBuilder();
            string bd = CommonManager.Web.RequestUrlDecode("bd", "");
            string ed = CommonManager.Web.RequestUrlDecode("ed", "");
            string un = CommonManager.Web.RequestUrlDecode("un", "");
            string type = CommonManager.Web.RequestUrlDecode("ty", "");
            string utype = CommonManager.Web.RequestUrlDecode("uty", "");
            string ct = CommonManager.Web.RequestUrlDecode("ct", "");

            if (!string.IsNullOrEmpty(bd) && CommonManager.String.IsDateTime(bd))
            {
                where.Append(" and InputDate>='" + bd + "'");
            }
            if (!string.IsNullOrEmpty(ed) && CommonManager.String.IsDateTime(ed))
            {
                where.Append(" and InputDate<='" + ed + "'");
            }
            if (!string.IsNullOrEmpty(ct))
            {
                where.Append(" and changeType=" + ct);
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
            //判断是否是根据玩家类别查询

            if (!string.IsNullOrEmpty(utype))
            {

                if (utype == "1")
                    where.Append(" and userid in (select userid from tusers where  isrobot=0)");
                if (utype == "2")
                    where.Append(" and userid in (select userid from tusers where  isrobot=1)");


            }

            //绑定记录
            //int count;
            //DataTable dt = BLL.AdminLog.Default.GetLogList( anpPageIndex.PageSize, PageIndex, where.ToString(), "ID desc,ActionDate desc", out count );
            DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
                    .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
                    .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
                    .AddInputParameter("@Columns", DbType.String, "*")
                    .AddInputParameter("@TableName", DbType.String, "Web_LotteriesLog")
                    .AddInputParameter("@Wheres", DbType.String, where.ToString())
                    .AddInputParameter("@KeyName", DbType.String, "ID")
                    .AddInputParameter("@OrderBy", DbType.String, "ID desc,InputDate desc")
                    .ToDataSet();

            if (ds.Tables.Count > 0)
            {
                anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
                anpPageIndex.CurrentPageIndex = PageIndex;

                if (ds.Tables[1].Rows.Count > 0)
                {
                    rptDataList.Visible = true;
                    ltNonData.Visible = false;
                    rptDataList.DataSource = ds.Tables[1];
                    rptDataList.DataBind();
                    this.lblShowSum.Text = "变化的" + UiCommon.StringConfig.GoldName + "总数：" + DbSession.Default.FromSql("select sum(convert(bigint,ChangeLotteries)) from Web_LotteriesLog where 1=1 " + where).ToScalar().ToString();
                }
                else
                {
                    rptDataList.Visible = false;
                    ltNonData.Visible = true;
                }
            }
        }
    }
 