- VoxelChunk (Node)
  - Owner of the mesh and the physics hitbox for a sinlge chunk
  - does not store any info
  
- ChunkData
- WorldData
  - Dumb data containers
  
- VoxelFiniteWorld (Node)
  - contains
    - VoxelChunks
    - WorldData
  - manages WorldData
  - orders the VoxelChunks to update
  - owner of the single instances of the AbstractChunkMeshers

- BlockData
- BlockRegistry
  - Dumb data containers
- BlockRegistryJuicer
  - Process into game-ready data
    - currently only includes generating a texture atlas from the textures
    
- AbstractChunkMesher
- NaiveChunkMesher
- GreedyChunkMesher
  - Different Strategies that can be used

===

- Player
  - Third Person
  - State machine controller
  - physiccccs
- Enemies
  - pathfinding needs access to data in VoxelFiniteWorld
