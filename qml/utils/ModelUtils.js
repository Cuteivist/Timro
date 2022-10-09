.pragma library

function isModelAnArray(model) {
    return Array.isArray(model)
}

function isModelQml(model) {
    return model.toString().indexOf('QQmlListModel') !== -1
}

function hasRole(model, role) {
    if (model.count === 0 || isModelAnArray(model)) {
        console.error(model.count + "  " + isModelAnArray(model))
        return false
    }

    if (isModelQml(model)) {
        return (typeof model.get(0)[role] !== 'undefined')
    }

    return model.roles().indexOf(role) !== -1
}

function getValue(model, index, role) {
    if (model === undefined || model === null)
        return null;

    if (model.count <= index || index < 0) {
        console.warn("Index out of bounds: " + index + " model " + model + " count = " + model.count)
        return null
    }

    if (isModelAnArray(model)) {
        return model[index]
    }

    if (role !== "" && !hasRole(model, role)) {
        console.warn("Model '%1' doesn't have role '%2'. Roles: %3".arg(model).arg(role).arg(model.roles ? model.roles() : ""))
        return null
    }

    if (isModelQml(model)) {
        return model.get(index)[role]
    }

    return model.data(index, role)
}
