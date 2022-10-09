.pragma library

function getMinutes(elapsedSeconds) {
    return (Math.floor(elapsedSeconds / 60)) % 60
}

function getHours(elapsedSeconds) {
    return Math.floor(Math.floor(elapsedSeconds / 60) / 60)
}

function toString(elapsedSeconds) {
    let secs = elapsedSeconds % 60
    const fullMinutes = Math.floor(elapsedSeconds / 60)
    let mins = fullMinutes % 60
    let hours = Math.floor(fullMinutes / 60 )

    const secsStr = secs > 9 ? secs : '0' + secs
    const minsStr = mins > 9 ? mins : '0' + mins
    const hoursStr = hours > 9 ? hours : '0' + hours

    return hoursStr + ':' + minsStr + ':' + secsStr
}
