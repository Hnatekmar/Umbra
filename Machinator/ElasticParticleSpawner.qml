import QtQuick 2.0
import Umbra 1.0

SelectionRectangle {
    width: 50
    id: selector

    ParticleDefinition
    {
        id: definition
        flags: [
            ParticleFlag{
                flag: ParticleFlag.ELASTIC
            },
            ParticleFlag{
                flag: ParticleFlag.SPRING
            }
        ]
        lifetime: 2
        strength: 1.0
    }
    onReleased: {
       var colors = ["red", "blue", "yellow", "white", "purple", "cyan", "black", "green", "orange"]
       definition.color = colors[Math.floor((Math.random() * colors.length))]
       definition.lifetime = -1.0
       myLayer.createParticleBox(Qt.rect(rect.x + rect.width / 2, rect.y + rect.height / 2, rect.width, rect.height), definition)
       destroy()
    }
}
