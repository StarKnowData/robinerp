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
namespace Bzw.Inhersits.Manage
{
   public partial class Manage_BankMoneyOperaLog : UiCommon.ManageBasePage
{

        /// <summary>
    /// Head1 控件。
    /// </summary>
    /// <remarks>
    /// 自动生成的字段。
    /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
    /// </remarks>
    protected global::System.Web.UI.HtmlControls.HtmlHead Head1;
    
    /// <summary>
    /// webmeta1 控件。
    /// </summary>
    /// <remarks>
    /// 自动生成的字段。
    /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
    /// </remarks>
    protected global::System.Web.UI.UserControl webmeta1;
    
    /// <summary>
    /// form1 控件。
    /// </summary>
    /// <remarks>
    /// 自动生成的字段。
    /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
    /// </remarks>
    protected global::System.Web.UI.HtmlControls.HtmlForm form1;
    
    /// <summary>
    /// webtop1 控件。
    /// </summary>
    /// <remarks>
    /// 自动生成的字段。
    /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
    /// </remarks>
    protected global::System.Web.UI.UserControl webtop1;
    
    /// <summary>
    /// Left1 控件。
    /// </summary>
    /// <remarks>
    /// 自动生成的字段。
    /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
    /// </remarks>
    protected global::System.Web.UI.UserControl Left1;
    
    /// <summary>
    /// webuserlogin1 控件。
    /// </summary>
    /// <remarks>
    /// 自动生成的字段。
    /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
    /// </remarks>
    protected global::System.Web.UI.UserControl webuserlogin1;
    

    
    /// <summary>
    /// rpList 控件。
    /// </summary>
    /// <remarks>
    /// 自动生成的字段。
    /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
    /// </remarks>
    protected global::System.Web.UI.WebControls.Repeater rpList;
    
    /// <summary>
    /// anpPageIndex 控件。
    /// </summary>
    /// <remarks>
    /// 自动生成的字段。
    /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
    /// </remarks>
    protected global::Wuqi.Webdiyer.AspNetPager anpPageIndex;
    
    /// <summary>
    /// webfooter1 控件。
    /// </summary>
    /// <remarks>
    /// 自动生成的字段。
    /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
    /// </remarks>
    protected global::System.Web.UI.UserControl webfooter1;
    //序号
    public int Rowid = 0;

	protected int PageIndex
	{
		get
		{
			string pi = CommonManager.Web.Request( "page", "" );
			if( string.IsNullOrEmpty( pi ) || !CommonManager.String.IsInteger( pi ) )
				return 1;
			return int.Parse( pi );
		}
	}	

    protected void Page_Load(object sender, EventArgs e)
    {		
		if (!IsPostBack)
		{
			BindLogList();					
		}
    }

    public void BindLogList()
    {
		StringBuilder where = new StringBuilder();
		where.AppendFormat(" and UserID='{0}' ",UiCommon.UserLoginInfo.UserID);
		string bd = CommonManager.Web.RequestUrlDecode("bd", "");
		string ed = CommonManager.Web.RequestUrlDecode("ed", "");
		string type = CommonManager.Web.RequestUrlDecode("type", "");
		if (!string.IsNullOrEmpty(bd) && CommonManager.String.IsDateTime(bd))
		{
			where.AppendFormat(" and TimeEx>='{0} 00:00:00'", bd);
		}
		if (!string.IsNullOrEmpty(ed) && CommonManager.String.IsDateTime(ed))
		{
			where.AppendFormat(" and TimeEx<='{0} 23:59:59'", ed);
		}
		if (CommonManager.String.IsInteger(type))
		{
			if (type.Equals("1"))
			{
				where.Append(" and OutMoney>0");
			}
			else if(type.Equals("2"))
			{
				where.Append( " and InMoney>0");
			}
		}
		if( string.IsNullOrEmpty( where.ToString() ) )
			return;

		DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
		   .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
		   .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
		   .AddInputParameter("@Columns", DbType.String, "*")
		   .AddInputParameter("@TableName", DbType.String, "Web_VMoneyChangeRecord")
		   .AddInputParameter("@Wheres", DbType.String, where.ToString())
		   .AddInputParameter("@KeyName", DbType.String, "ID")
		   .AddInputParameter("@OrderBy", DbType.String, "TimeEx desc")
		   .ToDataSet();
		if (ds.Tables.Count > 0 && ds.Tables[1].Rows.Count > 0)
		{
			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex;

			rpList.DataSource = ds.Tables[1];
			rpList.DataBind();
			rpList.Visible = true;
			
		}
		else
		{			
			rpList.Visible = false;
		}		
    } 
   
}
}
