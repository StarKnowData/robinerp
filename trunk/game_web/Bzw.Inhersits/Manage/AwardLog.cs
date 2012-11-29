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


namespace Bzw.Inhersits.Manage
{
    public partial class Manage_AwardLog : UiCommon.ManageBasePage
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
    /// form11 控件。
    /// </summary>
    /// <remarks>
    /// 自动生成的字段。
    /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
    /// </remarks>
    protected global::System.Web.UI.HtmlControls.HtmlForm form11;
    
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
    /// webservice1 控件。
    /// </summary>
    /// <remarks>
    /// 自动生成的字段。
    /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
    /// </remarks>
    protected global::System.Web.UI.UserControl webservice1;
    
    /// <summary>
    /// webtop1 控件。
    /// </summary>
    /// <remarks>
    /// 自动生成的字段。
    /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
    /// </remarks>
    protected global::System.Web.UI.UserControl webtop1;
    
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
    /// Control1 控件。
    /// </summary>
    /// <remarks>
    /// 自动生成的字段。
    /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
    /// </remarks>
    protected global::System.Web.UI.UserControl Control1;

        //序号
        public int Rowid = 0;

        protected int PageIndex
        {
            get
            {
                string pi = CommonManager.Web.Request("page", "");
                if (string.IsNullOrEmpty(pi) || !CommonManager.String.IsInteger(pi))
                    return 1;
                return int.Parse(pi);
            }
        }

        protected void Page_Load(object sender, EventArgs e)
        {
            BindLogList();

        }

        public void BindLogList()
        {
            string where = " and UserID='" + UiCommon.UserLoginInfo.UserID + "'";
            int counts = 0;
            DataTable dt = Utility.SqlHelper.ExecuteDataPager("Web_vAwardRecord", "Award_ID", "*", "AwardTime", 1, anpPageIndex.PageSize, anpPageIndex.CurrentPageIndex, out counts, where);
            anpPageIndex.RecordCount = counts;
            rpList.DataSource = dt.DefaultView;
            rpList.DataBind();
        }


    }
}
