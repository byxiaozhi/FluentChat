interface IPage {
    title: string,
    path: string,
    element?: JSX.Element
    auth?: (string) => bool
}

type IPageList = IPage[]