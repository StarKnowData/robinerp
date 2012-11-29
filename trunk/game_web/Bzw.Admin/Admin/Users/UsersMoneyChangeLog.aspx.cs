using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using BCST.Common;
using System.Text;
using Bzw.Data;

public partial class Admin_Users_UsersMoneyChangeLog : AdminBasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
		//处理页面指令
		/*switch( Action )
		{
			case "del"://删除单条
				if( IntParam != 0 )
				{
					//BLL.AdminLog.Default.Delete( IntParam );
					DbSession.Default.FromSql( "delete Web_MoneyChangeLog where RecordID=" + IntParam ).Execute();
				}
				CommonManager.Web.RegJs( this, "RefreshMeDelParam('[\\\\?&]action=del&params=(\\\\d)+')", false );
				break;
			case "delall"://删除全部
				//BLL.AdminLog.Default.Clear();
				DbSession.Default.FromSql( "delete Web_MoneyChangeLog" ).Execute();
				CommonManager.Web.RegJs( this, "RefreshMeDelParam('[\\\\?&]action=delall')", false );
				break;
		}*/

		//获取搜索条件
		StringBuilder where = new StringBuilder();
		string bd = CommonManager.Web.RequestUrlDecode( "bd", "" );
		string ed = CommonManager.Web.RequestUrlDecode( "ed", "" );
		string un = CommonManager.Web.RequestUrlDecode( "un", "" );
		string type = CommonManager.Web.RequestUrlDecode( "ty", "" );
        string utype =CommonManager.Web.RequestUrlDecode("uty", "");
        string ct = CommonManager.Web.RequestUrlDecode("ct", "");

		if( !string.IsNullOrEmpty( bd ) && CommonManager.String.IsDateTime( bd ) )
		{
			where.Append( " and dateTime>='" + bd + "'" );
		}
		if( !string.IsNullOrEmpty( ed ) && CommonManager.String.IsDateTime( ed ) )
		{
			where.Append( " and dateTime<='" + ed + "'" );
		}
        if (!string.IsNullOrEmpty(ct))
        {
            where.Append(" and changeType=" + ct);
        }
		//判断根据用户名还是用户ID
		if( !string.IsNullOrEmpty( un ) )
		{
			if( type == "byname" )
			{
				where.Append( " and UserName='" + un + "'" );
			}
			else
			{
				if( CommonManager.String.IsInteger( un ) )
				{
					where.Append( " and UserID='" + un + "'" );
				}
				else
				{
					CommonManager.Web.RegJs( this, "alert('"+ChineseMessage.userIdFormatErrorMessage+"')", false );
				}
			}
			
		}
        //判断是否是根据玩家类别查询,默认真实玩家

        if (!string.IsNullOrEmpty(utype))
        {

            if (utype == "2")
                where.Append(" and userid in (select userid from tusers where  isrobot=1)");
            if (utype == "1")
                where.Append(" and userid in (select userid from tusers where  isrobot=0)");
        }
        else
        {
            where.Append(" and userid in (select userid from tusers where  isrobot=0)");
        }
        
		//绑定记录
		//int count;
		//DataTable dt = BLL.AdminLog.Default.GetLogList( anpPageIndex.PageSize, PageIndex, where.ToString(), "ID desc,ActionDate desc", out count );
		DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
				.AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
				.AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
				.AddInputParameter( "@Columns", DbType.String, "*" )
                .AddInputParameter("@TableName", DbType.String, string.IsNullOrEmpty(un) ? "Web_MoneyChangeLog" : "Web_vUserAllMoneyChangeLog")
				.AddInputParameter( "@Wheres", DbType.String, where.ToString() )
				.AddInputParameter( "@KeyName", DbType.String, "DateTime" )
				.AddInputParameter( "@OrderBy", DbType.String, "dateTime desc" )
				.ToDataSet();

		if( ds.Tables.Count > 0 )
		{
			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex;

			if( ds.Tables[1].Rows.Count > 0 )
			{
				rptDataList.Visible = true;
				ltNonData.Visible = false;
				rptDataList.DataSource = ds.Tables[1];
				rptDataList.DataBind();
                this.lblShowSum.Text = "变化的金币总数：" + DbSession.Default.FromSql("select sum(convert(bigint,ChangeMoney)) from Web_vUserAllMoneyChangeLog where 1=1 " + where).ToScalar().ToString();
			}
			else
			{
				rptDataList.Visible = false;

				ltNonData.Visible = true;
			}
		}
    }
}
