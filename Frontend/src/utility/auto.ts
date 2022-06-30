
const isAdmin = (role: string) => {
    return role == 'admin'
}

const isUploader = (role: string) => {
    return role == 'uploader' || isAdmin(role)
}

const isCollector = (role: string) => {
    return role == 'collector' || isAdmin(role)
}

export { isAdmin, isUploader, isCollector }