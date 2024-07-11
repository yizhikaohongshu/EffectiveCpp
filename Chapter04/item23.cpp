/**
 * item 23 : 宁以 non-member, non-friend 替换成员函数
*/

// 表示浏览器
class WebBrowser
{
public:
    void clearCache();
    void clearHistory();
    void removeCookies();

    // 许多客户会想一整个执行所有这些动作
    void clearEverything()
    {
        clearCache();
        clearHistory();
        clearHistory();
    }
};

// 上述机能也可由一个 non-member 函数调用适当的 member 函数而提供出来
void clearEverything(WebBrowser& wb)
{
    wb.clearCache();
    wb.clearHistory();
    wb.removeCookies();
}

// member 函数 和 non-member 函数那个好?
// 面向对象守则要求, 数据 以及 操作数据的那些函数 应该被捆绑在一块, 意味它建议 member 函数是较好的选择, 但是这个建议不正确.

// 面向对象守则要求数据应该尽可能被封装, member函数 clearEverything带来的封装性比 non-member函数带来的封装性要低

// 越多东西被封装, 越少人可以看到它, 越少人看到它, 就有越大的弹性去变化它.