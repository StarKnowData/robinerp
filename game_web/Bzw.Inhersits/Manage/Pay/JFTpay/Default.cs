using System;
using System.Collections.Generic;
using System.Text;
using Bzw.WebLibrary;
using Utility;
using System.Data;
using System.Data.SqlClient;

namespace Bzw.Inhersits
{
    public partial class Manage_Pay_JFTpay_Default : UiCommon.BasePage 
    {

        /// <summary>
        /// Head1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlHead Head1;

        /// <summary>
        /// webmeta1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webmeta1;

        /// <summary>
        /// webTopOne 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webTopOne;

        /// <summary>
        /// webshortcutkey1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webshortcutkey1;

        /// <summary>
        /// webservice1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webservice1;

        /// <summary>
        /// lblMsg 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Label lblMsg;

        /// <summary>
        /// webFooterone 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webFooterone;




        protected string MoneyRate = string.Empty;
        protected string username = string.Empty;

        protected string CouponRate = string.Empty;

        protected void Page_Load(object sender, EventArgs e)
        {
            SeoSetting(SeoConfig.Config.PaySeo);
            if (UiCommon.UserLoginInfo.IsLogin)
            {
                username = UiCommon.UserLoginInfo.UserName;
            }
            else
            {
                username = "";
            }
            MoneyRate = BLL.Config.GetInfoOfCard()["Con_MoneyChangeRate"].ToString();
            //CouponRate = GetCouponRate();
        }

        private string GetCouponRate()
        {
            string strsql = "select top 1 CouponRate from TRechargeCouponType where Way=@way";
            DataTable table = SqlHelper.ExecuteDataset(
                CommandType.Text,
                strsql,
                new SqlParameter[]{
                    new SqlParameter("@way",6)
                }
                ).Tables[0];
            if (table.Rows.Count > 0)
            {
                return table.Rows[0]["CouponRate"].ToString();
            }
            return "";
        }
    }
}

